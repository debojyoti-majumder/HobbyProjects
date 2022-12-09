#include "commondefs.hpp"

#define	MDB_IDL_LOGN	16	/* DB_SIZE is 2^16, UM_SIZE is 2^17 */
#define MDB_IDL_DB_SIZE		(1<<MDB_IDL_LOGN)
#define MDB_IDL_UM_SIZE		(1<<(MDB_IDL_LOGN+1))

#define MDB_IDL_DB_MAX		(MDB_IDL_DB_SIZE-1)
#define MDB_IDL_UM_MAX		(MDB_IDL_UM_SIZE-1)

MDB_IDL mdb_midl_alloc(int num);
void mdb_midl_free(MDB_IDL ids);
int mdb_mid2l_insert( MDB_ID2L ids, MDB_ID2 *id );
int mdb_mid2l_append( MDB_ID2L ids, MDB_ID2 *id );
unsigned int mdb_mid2l_search( MDB_ID2L ids, MDB_ID id );

#define CMP(x,y)	 ( (x) < (y) ? -1 : (x) > (y) )

#define mdb_midl_xappend(idl, id) do { \
		MDB_ID *xidl = (idl), xlen = ++(xidl[0]); \
		xidl[xlen] = (id); \
	} while (0)

static int
mdb_cmp_cint(const MDB_val *a, const MDB_val *b);
