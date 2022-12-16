#pragma once

#include "commondefs.hpp"
#include <pthread.h>
#include "mdb_cursor.hpp"

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
struct MDB_env;
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
