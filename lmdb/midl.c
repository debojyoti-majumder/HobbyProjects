#include "midl.h"

MDB_IDL mdb_midl_alloc(int num)
{
	MDB_IDL ids = (MDB_IDL) malloc((num+2) * sizeof(MDB_ID));
	if (ids) {
		*ids++ = num;
		*ids = 0;
	}
	return ids;
}

void mdb_midl_free(MDB_IDL ids)
{
	if (ids)
		free(ids-1);
}

unsigned mdb_mid2l_search( MDB_ID2L ids, MDB_ID id )
{
	/*
	 * binary search of id in ids
	 * if found, returns position of id
	 * if not found, returns first position greater than id
	 */
	unsigned base = 0;
	unsigned cursor = 1;
	int val = 0;
	unsigned n = (unsigned)ids[0].mid;

	while( 0 < n ) {
		unsigned pivot = n >> 1;
		cursor = base + pivot + 1;
		val = CMP( id, ids[cursor].mid );

		if( val < 0 ) {
			n = pivot;

		} else if ( val > 0 ) {
			base = cursor;
			n -= pivot + 1;

		} else {
			return cursor;
		}
	}

	if( val > 0 ) {
		++cursor;
	}
	return cursor;
}

int mdb_mid2l_append( MDB_ID2L ids, MDB_ID2 *id )
{
	/* Too big? */
	if (ids[0].mid >= MDB_IDL_UM_MAX) {
		return -2;
	}
	ids[0].mid++;
	ids[ids[0].mid] = *id;
	return 0;
}

int mdb_mid2l_insert( MDB_ID2L ids, MDB_ID2 *id )
{
	unsigned x, i;

	x = mdb_mid2l_search( ids, id->mid );

	if( x < 1 ) {
		/* internal error */
		return -2;
	}

	if ( x <= ids[0].mid && ids[x].mid == id->mid ) {
		/* duplicate */
		return -1;
	}

	if ( ids[0].mid >= MDB_IDL_UM_MAX ) {
		/* too big */
		return -2;

	} else {
		/* insert id */
		ids[0].mid++;
		for (i=(unsigned)ids[0].mid; i>x; i--)
			ids[i] = ids[i-1];
		ids[x] = *id;
	}

	return 0;
}

static int
mdb_cmp_cint(const MDB_val *a, const MDB_val *b)
{
#if BYTE_ORDER == LITTLE_ENDIAN
	unsigned short *u, *c;
	int x;

	u = (unsigned short *) ((char *) a->mv_data + a->mv_size);
	c = (unsigned short *) ((char *) b->mv_data + a->mv_size);
	do {
		x = *--u - *--c;
	} while(!x && u > (unsigned short *)a->mv_data);
	return x;
#else
	return memcmp(a->mv_data, b->mv_data, a->mv_size);
#endif
}
