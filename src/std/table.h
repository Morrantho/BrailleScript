#define TABLE_LOAD 0.6

typedef struct Table
{
	String *base;
	Arena *strings;
	U32 len;
	U32 max;
} Table;

Table *GetInterns( )
{
	static Table interns = { 0 };
	return &interns;
}

Void TableAlloc( Table *table, Arena *strings, U32 max )
{
	table->strings = strings;
	table->base = calloc( max, sizeof( String ) );
	table->len = 0;
	table->max = max;
}

String *TableFind( Table *table, I8 *str_a, U32 len, U32 hash )
{
	U32 idx = hash & ( table->max - 1 );
	for( ;; idx = ( idx + 1 ) & ( table->max - 1 ) )
	{
		String *str = &table->base[ idx ];
		if( !str->hash ){ return str; }
		if( str->len != len ){ continue; }
		I8 *str_b = ( I8* )table->strings->base + str->offset;
		I32 cmp = memcmp( str_a, str_b, len );
		if( cmp == 0 ){ return str; }
	}
}

Void TableReput( Table *table, String *old_str )
{
	I8 *old_cstr = ArenaOff( table->strings, old_str->offset );
	String *new_str = TableFind( table, old_cstr, old_str->len, old_str->hash );
	table->len++;
	new_str->offset = old_str->offset;
	new_str->len = old_str->len;
	new_str->hash = old_str->hash;
}

Void TableGrow( Table *table )
{
	String *old_base = table->base;
	U32 old_len = table->len;
	TableAlloc( table, table->strings, table->max << 1 );
	for( U32 i = 0; i < old_len; i++ )
	{
		String *old_str = &old_base[ i ];
		if( !old_str->hash ){ continue; } /* skip empty / tombstones */
		TableReput( table, old_str ); /* reinsert at new hash index */
	}
	free( old_base );
}

String *TablePut( Table *table, I8 *src, U32 len )
{
	if( table->len > table->max * TABLE_LOAD ){ TableGrow( table ); }
	U32 hash = StringHash( src, len );
	String *str = TableFind( table, src, len, hash );
	if( str->hash ){ return str; }
	table->len++;
	
	str->offset = StringAlloc( table->strings, src, len );
	str->len = len;
	str->hash = hash;
	return str;
}