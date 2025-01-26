#ifndef BS_TABLE_H
#define BS_TABLE_H

#define TABLE_LOAD 0.65

typedef struct table
{
	u32* base;
	arena* strings;
	u32 len;
	u32 max;
} table;

typedef struct table_res
{
	str* found; /* str */
	u32 idx;
} table_res;

void table_init( table* table, arena* strings, u32 max )
{
	table->base = calloc( max, sizeof( u32 ) );
	table->strings = strings;
	table->len = 0;
	table->max = max;
}

stil table_res table_find( table* table, i8* src, u32 len, u32 hash )
{
	table_res res = { 0 }; /* .found inits null */
	u32 idx = hash & ( table->max - 1 );
	for( ;; )
	{
		u32 offset = table->base[ idx ];
		if( !offset ){ res.idx = idx; return res; }
		idx = ( idx + 1 ) & ( table->max - 1 );
		str* pstr = arena_ptr( table->strings, offset );
		if( len != pstr->len ){ continue; }
		i8* dest = ( i8* )( pstr + 1 );
		if( memcmp( src, dest, len ) != 0 ){ continue; }
		res.found = pstr;
		return res;
	}
}

void table_reput( table* table, u32 ooff )
{
	str* ostr = arena_ptr( table->strings, ooff );
	i8* ocstr = ( i8* )( ostr + 1 ); /* past struct */
	table_res res = table_find( table, ocstr, ostr->len, ostr->hash );
	// if( res.found ){ ?? } /* mass confusion if true */
	table->base[ res.idx ] = ooff; /* retain old offset */
	table->len++;
}

void table_grow( table* table )
{
	u32* offsets = table->base;
	u32 max = table->max;
	table_init( table, table->strings, table->max << 1 );
	for( u32 i = 0; i < max; i++ )
	{
		u32 offset = offsets[ i ];
		if( !offset ){ continue; }
		table_reput( table, offset );
	}
	free( offsets );
}

str* table_put( table* table, i8* src, u32 len )
{
	if( table->len > table->max * TABLE_LOAD ){ table_grow( table ); }
	u32 hash = str_hash( src, len );
	table_res tab_res = table_find( table, src, len, hash );
	if( tab_res.found ){ return tab_res.found; }
	str_res str_res = str_alloc( table->strings, src, len, hash );
	table->base[ tab_res.idx ] = str_res.offset;
	table->len++;
	return str_res.str;
}

#endif