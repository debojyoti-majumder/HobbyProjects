#pragma once

#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef size_t MDB_ID;
typedef MDB_ID pgno_t;
typedef MDB_ID txnid_t;
typedef unsigned int MDB_dbi;
typedef MDB_ID *MDB_IDL;
typedef struct MDB_ID2 {
	MDB_ID mid;		/**< The ID */
	void *mptr;		/**< The pointer */
} MDB_ID2;
typedef MDB_ID2 *MDB_ID2L;
typedef uint16_t	 indx_t;

#define	HANDLE	int
#define CURSOR_STACK		 32
#define MDB_PID_T	pid_t
#ifndef CACHELINE
#define CACHELINE	64
#endif
#define MNAME_LEN	32
#define MDB_DUPSORT		0x04

#define MDB_PS_MODIFY	1
#define MDB_PS_ROOTONLY	2
#define MDB_PS_FIRST	4
#define MDB_PS_LAST		8

typedef struct MDB_val {
	size_t		 mv_size;	/**< size of the data item */
	void		*mv_data;	/**< address of the data item */
} MDB_val;

typedef int  (MDB_cmp_func)(const MDB_val *a, const MDB_val *b);
typedef void (MDB_rel_func)(MDB_val *item, void *oldptr, void *newptr, void *relctx);

typedef struct MDB_dbx {
	MDB_val		md_name;		/**< name of the database */
	MDB_cmp_func	*md_cmp;	/**< function for comparing keys */
	MDB_cmp_func	*md_dcmp;	/**< function for comparing data items */
	MDB_rel_func	*md_rel;	/**< user relocate function */
	void		*md_relctx;		/**< user-provided context for md_rel */
} MDB_dbx;

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

// MDB Consts
#define MDB_SUCCESS	 0
	/** key/data pair already exists */
#define MDB_KEYEXIST	(-30799)
	/** key/data pair not found (EOF) */
#define MDB_NOTFOUND	(-30798)
	/** Requested page not found - this usually indicates corruption */
#define MDB_PAGE_NOTFOUND	(-30797)
	/** Located page was wrong type */
#define MDB_CORRUPTED	(-30796)
	/** Update of meta page failed, probably I/O error */
#define MDB_PANIC		(-30795)
	/** Environment version mismatch */
#define MDB_VERSION_MISMATCH	(-30794)
	/** File is not a valid MDB file */
#define MDB_INVALID	(-30793)
	/** Environment mapsize reached */
#define MDB_MAP_FULL	(-30792)
	/** Environment maxdbs reached */
#define MDB_DBS_FULL	(-30791)
	/** Environment maxreaders reached */
#define MDB_READERS_FULL	(-30790)
	/** Too many TLS keys in use - Windows only */
#define MDB_TLS_FULL	(-30789)
	/** Txn has too many dirty pages */
#define MDB_TXN_FULL	(-30788)
	/** Cursor stack too deep - internal error */
#define MDB_CURSOR_FULL	(-30787)
	/** Page has not enough space - internal error */
#define MDB_PAGE_FULL	(-30786)
	/** Database contents grew beyond environment mapsize */
#define MDB_MAP_RESIZED	(-30785)
	/** MDB_INCOMPATIBLE: Operation and DB incompatible, or DB flags changed */
#define MDB_INCOMPATIBLE	(-30784)
	/** Invalid reuse of reader locktable slot */
#define MDB_BAD_RSLOT		(-30783)
	/** Transaction cannot recover - it must be aborted */
#define MDB_BAD_TXN			(-30782)
	/** Too big key/data, key is empty, or wrong DUPFIXED size */
#define MDB_BAD_VALSIZE		(-30781)
#define MDB_LAST_ERRCODE	MDB_BAD_VALSIZE

#define P_INVALID	 (~(pgno_t)0)

	/** Handle for the DB used to track free pages. */
#define	FREE_DBI	0
	/** Handle for the default DB. */
#define	MAIN_DBI	1

	/** mdb_dbi_open flags */
#define MDB_VALID	0x8000		/**< DB handle is valid, for me_dbflags */
#define PERSISTENT_FLAGS	(0xffff & ~(MDB_VALID))
#define VALID_FLAGS	(MDB_REVERSEKEY|MDB_DUPSORT|MDB_INTEGERKEY|MDB_DUPFIXED|\
	MDB_INTEGERDUP|MDB_REVERSEDUP|MDB_CREATE)

	/** Test if the flags \b f are set in a flag word \b w. */
#define F_ISSET(w, f)	 (((w) & (f)) == (f))
