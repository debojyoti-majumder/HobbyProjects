/** @file main.cpp
 *	@brief memory-mapped database library
 *
 *	A Btree-based database management library modeled loosely on the
 *	BerkeleyDB API, but much simplified.
 */
/*
 * Copyright 2011-2013 Howard Chu, Symas Corp.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted only as authorized by the OpenLDAP
 * Public License.
 *
 * A copy of this license is available in the file LICENSE in the
 * top-level directory of the distribution or, alternatively, at
 * <http://www.OpenLDAP.org/license.html>.
 *
 * This code is derived from btree.c written by Martin Hedenfalk.
 *
 * Copyright (c) 2009, 2010 Martin Hedenfalk <martin@bzero.se>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include <iostream>
#include <semaphore.h>

using namespace std;

typedef size_t MDB_ID;
typedef MDB_ID pgno_t;
typedef MDB_ID txnid_t;
typedef unsigned int MDB_dbi;
typedef MDB_ID *MDB_IDL;
typedef uint16_t	 indx_t;

#define	HANDLE	int
#define CURSOR_STACK		 32
#define MDB_PID_T	pid_t
#ifndef CACHELINE
#define CACHELINE	64
#endif
#define MNAME_LEN	32

typedef struct MDB_val {
	size_t		 mv_size;	/**< size of the data item */
	void		*mv_data;	/**< address of the data item */
} MDB_val;

/** @brief A callback function used to compare two keys in a database */
typedef int  (MDB_cmp_func)(const MDB_val *a, const MDB_val *b);
typedef void (MDB_rel_func)(MDB_val *item, void *oldptr, void *newptr, void *relctx);
typedef void MDB_assert_func(MDB_env *env, const char *msg);

typedef struct MDB_dbx {
	MDB_val		md_name;		/**< name of the database */
	MDB_cmp_func	*md_cmp;	/**< function for comparing keys */
	MDB_cmp_func	*md_dcmp;	/**< function for comparing data items */
	MDB_rel_func	*md_rel;	/**< user relocate function */
	void		*md_relctx;		/**< user-provided context for md_rel */
} MDB_dbx;

	/** An ID2 is an ID/pointer pair.
	 */
typedef struct MDB_ID2 {
	MDB_ID mid;		/**< The ID */
	void *mptr;		/**< The pointer */
} MDB_ID2;

	/** An ID2L is an ID2 List, a sorted array of ID2s.
	 * The first element's \b mid member is a count of how many actual
	 * elements are in the array. The \b mptr member of the first element is unused.
	 * The array is sorted in ascending order by \b mid.
	 */
typedef MDB_ID2 *MDB_ID2L;

typedef struct MDB_rxbody {
	/**	Current Transaction ID when this transaction began, or (txnid_t)-1.
	 *	Multiple readers that start at the same time will probably have the
	 *	same ID here. Again, it's not important to exclude them from
	 *	anything; all we need to know is which version of the DB they
	 *	started from so we can avoid overwriting any data used in that
	 *	particular version.
	 */
	txnid_t		mrb_txnid;
	/** The process ID of the process owning this reader txn. */
	MDB_PID_T	mrb_pid;
	/** The thread ID of the thread owning this txn. */
	pthread_t	mrb_tid;
} MDB_rxbody;

	/** The actual reader record, with cacheline padding. */
typedef struct MDB_reader {
	union {
		MDB_rxbody mrx;
		/** shorthand for mrb_txnid */
#define	mr_txnid	mru.mrx.mrb_txnid
#define	mr_pid	mru.mrx.mrb_pid
#define	mr_tid	mru.mrx.mrb_tid
		/** cache line alignment */
		char pad[(sizeof(MDB_rxbody)+CACHELINE-1) & ~(CACHELINE-1)];
	} mru;
} MDB_reader;

typedef struct MDB_page {
#define	mp_pgno	mp_p.p_pgno
#define	mp_next	mp_p.p_next
	union {
		pgno_t		p_pgno;	/**< page number */
		void *		p_next;	/**< for in-memory list of freed structs */
	} mp_p;
	uint16_t	mp_pad;
/**	@defgroup mdb_page	Page Flags
 *	@ingroup internal
 *	Flags for the page headers.
 *	@{
 */
#define	P_BRANCH	 0x01		/**< branch page */
#define	P_LEAF		 0x02		/**< leaf page */
#define	P_OVERFLOW	 0x04		/**< overflow page */
#define	P_META		 0x08		/**< meta page */
#define	P_DIRTY		 0x10		/**< dirty page, also set for #P_SUBP pages */
#define	P_LEAF2		 0x20		/**< for #MDB_DUPFIXED records */
#define	P_SUBP		 0x40		/**< for #MDB_DUPSORT sub-pages */
#define	P_KEEP		 0x8000		/**< leave this page alone during spill */
/** @} */
	uint16_t	mp_flags;		/**< @ref mdb_page */
#define mp_lower	mp_pb.pb.pb_lower
#define mp_upper	mp_pb.pb.pb_upper
#define mp_pages	mp_pb.pb_pages
	union {
		struct {
			indx_t		pb_lower;		/**< lower bound of free space */
			indx_t		pb_upper;		/**< upper bound of free space */
		} pb;
		uint32_t	pb_pages;	/**< number of overflow pages */
	} mp_pb;
	indx_t		mp_ptrs[1];		/**< dynamic size */
} MDB_page;

	/** State of FreeDB old pages, stored in the MDB_env */
typedef struct MDB_pgstate {
	pgno_t		*mf_pghead;	/**< Reclaimed freeDB pages, or NULL before use */
	txnid_t		mf_pglast;	/**< ID of last used record, or 0 if !mf_pghead */
} MDB_pgstate;

typedef struct MDB_txbody {
		/** Stamp identifying this as an MDB file. It must be set
		 *	to #MDB_MAGIC. */
	uint32_t	mtb_magic;
		/** Format of this lock file. Must be set to #MDB_LOCK_FORMAT. */
	uint32_t	mtb_format;

	pthread_mutex_t	mtb_mutex;
		/**	The ID of the last transaction committed to the database.
		 *	This is recorded here only for convenience; the value can always
		 *	be determined by reading the main database meta pages.
		 */
	txnid_t		mtb_txnid;
		/** The number of slots that have been used in the reader table.
		 *	This always records the maximum count, it is not decremented
		 *	when readers release their slots.
		 */
	unsigned	mtb_numreaders;
} MDB_txbody;

	/** The actual reader table definition. */
typedef struct MDB_txninfo {
	union {
		MDB_txbody mtb;
#define mti_magic	mt1.mtb.mtb_magic
#define mti_format	mt1.mtb.mtb_format
#define mti_mutex	mt1.mtb.mtb_mutex
#define mti_rmname	mt1.mtb.mtb_rmname
#define mti_txnid	mt1.mtb.mtb_txnid
#define mti_numreaders	mt1.mtb.mtb_numreaders
		char pad[(sizeof(MDB_txbody)+CACHELINE-1) & ~(CACHELINE-1)];
	} mt1;
	union {
#if (defined(_WIN32) && !(defined(HAVE_PTHREADS_WIN32))) || defined(MDB_USE_POSIX_SEM)
		char mt2_wmname[MNAME_LEN];
#define	mti_wmname	mt2.mt2_wmname
#else
		pthread_mutex_t	mt2_wmutex;
#define mti_wmutex	mt2.mt2_wmutex
#endif
		char pad[(MNAME_LEN+CACHELINE-1) & ~(CACHELINE-1)];
	} mt2;
	MDB_reader	mti_readers[1];
} MDB_txninfo;

/** Information about a single database in the environment. */
typedef struct MDB_db {
	uint32_t	md_pad;		/**< also ksize for LEAF2 pages */
	uint16_t	md_flags;	/**< @ref mdb_dbi_open */
	uint16_t	md_depth;	/**< depth of this tree */
	pgno_t		md_branch_pages;	/**< number of internal pages */
	pgno_t		md_leaf_pages;		/**< number of leaf pages */
	pgno_t		md_overflow_pages;	/**< number of overflow pages */
	size_t		md_entries;		/**< number of data items */
	pgno_t		md_root;		/**< the root page of this tree */
} MDB_db;

typedef struct MDB_meta {
		/** Stamp identifying this as an MDB file. It must be set
		 *	to #MDB_MAGIC. */
	uint32_t	mm_magic;
		/** Version number of this lock file. Must be set to #MDB_DATA_VERSION. */
	uint32_t	mm_version;
	void		*mm_address;		/**< address for fixed mapping */
	size_t		mm_mapsize;			/**< size of mmap region */
	MDB_db		mm_dbs[2];			/**< first is free space, 2nd is main db */
	/** The size of pages used in this DB */
#define	mm_psize	mm_dbs[0].md_pad
	/** Any persistent environment flags. @ref mdb_env */
#define	mm_flags	mm_dbs[0].md_flags
	pgno_t		mm_last_pg;			/**< last used page in file */
	txnid_t		mm_txnid;			/**< txnid that committed this page */
} MDB_meta;

struct MDB_env {
	HANDLE		me_fd;		/**< The main data file */
	HANDLE		me_lfd;		/**< The lock file */
	HANDLE		me_mfd;			/**< just for writing the meta pages */
	/** Failed to update the meta page. Probably an I/O error. */
#define	MDB_FATAL_ERROR	0x80000000U
	/** Some fields are initialized. */
#define	MDB_ENV_ACTIVE	0x20000000U
	/** me_txkey is set */
#define	MDB_ENV_TXKEY	0x10000000U
	/** Have liveness lock in reader table */
#define	MDB_LIVE_READER	0x08000000U
	uint32_t 	me_flags;		/**< @ref mdb_env */
	unsigned int	me_psize;	/**< DB page size, inited from me_os_psize */
	unsigned int	me_os_psize;	/**< OS page size, from #GET_PAGESIZE */
	unsigned int	me_maxreaders;	/**< size of the reader table */
	unsigned int	me_numreaders;	/**< max numreaders set by this env */
	MDB_dbi		me_numdbs;		/**< number of DBs opened */
	MDB_dbi		me_maxdbs;		/**< size of the DB table */
	MDB_PID_T	me_pid;		/**< process ID of this env */
	char		*me_path;		/**< path to the DB files */
	char		*me_map;		/**< the memory map of the data file */
	MDB_txninfo	*me_txns;		/**< the memory map of the lock file or NULL */
	MDB_meta	*me_metas[2];	/**< pointers to the two meta pages */
	void		*me_pbuf;		/**< scratch area for DUPSORT put() */
	MDB_txn		*me_txn;		/**< current write transaction */
	size_t		me_mapsize;		/**< size of the data memory map */
//	off_t		me_size;		/**< current file size */
	pgno_t		me_maxpg;		/**< me_mapsize / me_psize */
	MDB_dbx		*me_dbxs;		/**< array of static DB info */
	uint16_t	*me_dbflags;	/**< array of flags from MDB_db.md_flags */
	pthread_key_t	me_txkey;	/**< thread-key for readers */
	MDB_pgstate	me_pgstate;		/**< state of old pages from freeDB */
#	define		me_pglast	me_pgstate.mf_pglast
#	define		me_pghead	me_pgstate.mf_pghead
	MDB_page	*me_dpages;		/**< list of malloc'd blocks for re-use */
	/** IDL of pages that became unused in a write txn */
	MDB_IDL		me_free_pgs;
	/** ID2L of pages written during a write txn. Length MDB_IDL_UM_SIZE. */
	MDB_ID2L	me_dirty_list;
	/** Max number of freelist items that can fit in a single overflow page */
	int			me_maxfree_1pg;
	/** Max size of a node on a page */
	unsigned int	me_nodemax;
#if !(MDB_MAXKEYSIZE)
	unsigned int	me_maxkey;	/**< max size of a key */
#endif
	sem_t		*me_rmutex;		/* Shared mutexes are not supported */
	sem_t		*me_wmutex;
	void		*me_userctx;	 /**< User-settable context */
	MDB_assert_func *me_assert_func; /**< Callback for assertion failures */
};


struct MDB_txn {
	MDB_txn		*mt_parent;		/**< parent of a nested txn */
	MDB_txn		*mt_child;		/**< nested txn under this txn */
	pgno_t		mt_next_pgno;	/**< next unallocated page */

	/** The ID of this transaction. IDs are integers incrementing from 1.
	 *	Only committed write transactions increment the ID. If a transaction
	 *	aborts, the ID may be re-used by the next writer.
	 */
	txnid_t		mt_txnid;

	MDB_env		*mt_env;		/**< the DB environment */
	/** The list of pages that became unused during this transaction.
	 */
	MDB_IDL		mt_free_pgs;
	/** The sorted list of dirty pages we temporarily wrote to disk
	 *	because the dirty list was full. page numbers in here are
	 *	shifted left by 1, deleted slots have the LSB set.
	 */
	MDB_IDL		mt_spill_pgs;

	union {
		/** For write txns: Modified pages. Sorted when not MDB_WRITEMAP. */
		MDB_ID2L	dirty_list;
		/** For read txns: This thread/txn's reader table slot, or NULL. */
		MDB_reader	*reader;
	} mt_u;
	/** Array of records for each DB known in the environment. */
	MDB_dbx		*mt_dbxs;
	/** Array of MDB_db records for each known DB */
	MDB_db		*mt_dbs;
/** @defgroup mt_dbflag	Transaction DB Flags
 *	@ingroup internal
 * @{
 */
#define DB_DIRTY	0x01		/**< DB was modified or is DUPSORT data */
#define DB_STALE	0x02		/**< Named-DB record is older than txnID */
#define DB_NEW		0x04		/**< Named-DB handle opened in this txn */
#define DB_VALID	0x08		/**< DB handle is valid, see also #MDB_VALID */
/** @} */
	/** In write txns, array of cursors for each DB */
	MDB_cursor	**mt_cursors;
	/** Array of flags for each DB */
	unsigned char	*mt_dbflags;
	/**	Number of DB records in use. This number only ever increments;
	 *	we don't decrement it when individual DB handles are closed.
	 */
	MDB_dbi		mt_numdbs;

/** @defgroup mdb_txn	Transaction Flags
 *	@ingroup internal
 *	@{
 */
#define MDB_TXN_RDONLY		0x01		/**< read-only transaction */
#define MDB_TXN_ERROR		0x02		/**< an error has occurred */
#define MDB_TXN_DIRTY		0x04		/**< must write, even if dirty list is empty */
#define MDB_TXN_SPILLS		0x08		/**< txn or a parent has spilled pages */
/** @} */
	unsigned int	mt_flags;		/**< @ref mdb_txn */
	/** dirty_list room: Array size - #dirty pages visible to this txn.
	 *	Includes ancestor txns' dirty pages not hidden by other txns'
	 *	dirty/spilled pages. Thus commit(nested txn) has room to merge
	 *	dirty_list into mt_parent after freeing hidden mt_parent pages.
	 */
	unsigned int	mt_dirty_room;
};

struct MDB_cursor {
	/** Next cursor on this DB in this txn */
	MDB_cursor	*mc_next;
	/** Backup of the original cursor if this cursor is a shadow */
	MDB_cursor	*mc_backup;
	/** Context used for databases with #MDB_DUPSORT, otherwise NULL */
	struct MDB_xcursor	*mc_xcursor;
	/** The transaction that owns this cursor */
	MDB_txn		*mc_txn;
	/** The database handle this cursor operates on */
	MDB_dbi		mc_dbi;
	/** The database record for this cursor */
	MDB_db		*mc_db;
	/** The database auxiliary record for this cursor */
	MDB_dbx		*mc_dbx;
	/** The @ref mt_dbflag for this database */
	unsigned char	*mc_dbflag;
	unsigned short 	mc_snum;	/**< number of pushed pages */
	unsigned short	mc_top;		/**< index of top page, normally mc_snum-1 */
/** @defgroup mdb_cursor	Cursor Flags
 *	@ingroup internal
 *	Cursor state flags.
 *	@{
 */
#define C_INITIALIZED	0x01	/**< cursor has been initialized and is valid */
#define C_EOF	0x02			/**< No more data */
#define C_SUB	0x04			/**< Cursor is a sub-cursor */
#define C_DEL	0x08			/**< last op was a cursor_del */
#define C_SPLITTING	0x20		/**< Cursor is in page_split */
#define C_UNTRACK	0x40		/**< Un-track cursor when closing */
/** @} */
	unsigned int	mc_flags;	/**< @ref mdb_cursor */
	MDB_page	*mc_pg[CURSOR_STACK];	/**< stack of pushed pages */
	indx_t		mc_ki[CURSOR_STACK];	/**< stack of page indices */
};

/** @brief Opaque structure for navigating through a database */
typedef struct MDB_cursor MDB_cursor;

static int
mdb_page_search(MDB_cursor *mc, MDB_val *key, int flags)
{
}

int main() {
    return 0;
}
