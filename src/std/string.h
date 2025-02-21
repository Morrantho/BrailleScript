typedef struct String
{
	U32 offset; /* strings arena offset */
	U32 len;
	U32 hash;
} String;

U32 StringHash( I8 *cstr, U32 len )
{
	U32 hash = 2166136261U;
	U32 prime = 16777619U;
	for( U32 i = 0; i < len; i++ )
	{
		hash ^= cstr[ i ];
		hash *= prime;
	}
	return hash;
}

U32 StringAlloc( Arena *strings, I8 *src, U32 len )
{
	U32 offset = ArenaPush( strings, len, 1 );
	I8 *dest = ArenaOff( strings, offset );
	memcpy( dest, src, len );
	return offset;
}