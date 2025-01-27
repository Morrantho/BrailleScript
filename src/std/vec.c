/* Use the safe "s" variants if you are storing the pointers */
/* returned by a vec, so if it grows, the offsets are still valid. */

void vec_init( vec* vec, u32 szof, u32 max )
{
	vec->base = malloc( szof * max );
	vec->max = max;
	vec->szof = szof;
}

void* vec_ptr( vec* vec, offset off )
{
	return vec->base + ( off.idx * off.scl );
}

void vec_reset( vec* vec )
{
	vec->len = 0;
}

void vec_grow( vec* vec )
{
	vec->max <<= 1;
	vec->base = realloc( vec->base, vec->szof * vec->max );
}

u32 vec_push( vec* vec, void* value )
{
	if( vec->len >= vec->max ){ vec_grow( vec ); }
	i8* addr = vec->base + vec->len * vec->szof;
	memcpy( addr, value, vec->szof );
	return vec->len++;
}

void* vec_pop( vec* vec )
{
	if( vec->len == 0 ){ return vec->base; }
	return vec->base + ( --vec->len * vec->szof );
}

offset vec_pops( vec* vec )
{
	if( vec->len == 0 ){ return offset_init( 0, 0 ); }
	return offset_init( --vec->len, vec->szof );
}

void vec_set( vec* vec, u32 idx, void* value )
{
	if( idx >= vec->len ){ return; }
	i8* addr = vec->base + idx * vec->szof;
	memcpy( addr, value, vec->szof );
}

void* vec_get( vec* vec, u32 idx )
{
	if( idx >= vec->len ){ return vec->base; }
	return vec->base + idx * vec->szof;
}

offset vec_gets( vec* vec, u32 idx )
{
	if( idx >= vec->len ){ return offset_init( 0, 0 ); }
	return offset_init( idx, vec->szof );
}

void* vec_peek( vec* vec )
{
	if( vec->top == 0 ){ return vec->base; }
	return vec->base + ( ( vec->top - 1 ) * vec->szof );
}

offset vec_peeks( vec* vec )
{
	if( vec->top == 0 ){ return offset_init( 0, 0 ); }
	return offset_init( vec->top - 1, vec->szof );
}

void* vec_peekn( vec* vec, u32 idx )
{
	if( vec->top == 0 ){ return vec->base; }
	return vec->base + ( ( vec->top - 1 ) - idx ) * vec->szof;
}

offset vec_peekns( vec* vec, u32 idx )
{
	if( vec->top == 0 ){ return offset_init( 0, 0 ); }
	return offset_init( vec->top - 1 - idx, vec->szof );
}

void* vec_commit( vec* vec )
{
	if( vec->len >= vec->max ) { vec_grow( vec ); }
	return vec_get( vec, vec->len++ );
}

offset vec_commits( vec* vec )
{
	if( vec->len >= vec->max ) { vec_grow( vec ); }
	return vec_gets( vec, vec->len++ );
}

void vec_free( vec* vec )
{
	free( vec->base );
}
