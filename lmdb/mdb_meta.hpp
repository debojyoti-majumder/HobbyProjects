#pragma once
#include "commondefs.hpp"

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
