#ifndef BS_STRING_H
#define BS_STRING_H

typedef struct str
{	/* Add 1 to get its cstr: u8* cstr = ( u8* )( str + 1 ); */
	u32 len;
	u32 hash;
	// u8 flags;
} str;

typedef struct str_res
{
	str* str;
	u32 offset;
} str_res;

u32 str_hash( i8* cstr, u32 len )
{
	u32 hash = 2166136261U;
	for( u32 i = 0; i < len; i++ )
	{
		hash ^= cstr[ i ];
		hash *= 16777619U;
	}
	return hash;
}

str_res str_alloc( arena* strings, i8* src, u32 len, u32 hash )
{
	u32 szof = sizeof( str ) + len + 1;
	u32 offset = arena_alloc( strings, szof, 8 );
	str* pstr = ( str* )arena_ptr( strings, offset );
	pstr->hash = hash;
	pstr->len = len;
	// str->flags = 0;
	i8* dest = ( i8* )( pstr + 1 );
	memcpy( dest, src, len );
	dest[ len ] = '\0';
	return ( str_res ){ .str = pstr, .offset = offset };
}

#endif