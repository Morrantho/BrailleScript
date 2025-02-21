typedef struct Vec
{
	Void *base;
	union{ U32 len; U32 top; };
	U32 max;
	U32 szof;
} Vec;

Vec *GetConsts( )
{
	static Vec consts = { 0 };
	return &consts;
}

Vec *GetLocals( )
{
	static Vec locals = { 0 };
	return &locals;
}

Vec *GetGlobals( )
{
	static Vec globals = { 0 };
	return &globals;
}

Vec *GetCode( )
{
	static Vec code = { 0 };
	return &code;
}

Vec *GetFuncs( )
{
	static Vec funcs = { 0 };
	return &funcs;
}

Void VecAlloc( Vec *vec, U32 max, U32 szof )
{
	vec->base = malloc( max * szof );
	vec->len = 0;
	vec->max = max;
	vec->szof = szof;
}

Void *VecCommit( Vec *vec )
{
	if( vec->len > vec->max )
	{
		vec->max <<= 1;
		vec->base = realloc( vec->base, vec->max * vec->szof );
	}
	return ( I8* )vec->base + vec->len++ * vec->szof;
}

U32 VecPush( Vec *vec, Void *src )
{
	Void *dest = VecCommit( vec );
	memcpy( dest, src, vec->szof );
	return vec->len - 1;
}

Void *VecPop( Vec* vec )
{
	if( vec->len == 0 ){ return vec->base; }
	return ( I8* )vec->base + --vec->len * vec->szof;
}

Void VecSet( Vec *vec, U32 idx, Void *src )
{
	if( idx >= vec->len ){ return; }
	Void *dest = ( I8* )vec->base + idx * vec->szof;
	memcpy( dest, src, vec->szof );
}

Void *VecGet( Vec *vec, U32 idx )
{
	if( idx >= vec->len ){ return vec->base; }
	return ( I8* )vec->base + idx * vec->szof;
}

Void *VecPeek( Vec *vec )
{
	if( vec->len == 0 ){ return vec->base; }
	return ( I8* )vec->base + ( vec->len - 1 ) * vec->szof;
}

Void *VecPeekN( Vec *vec, U32 peek )
{
	if( peek >= vec->len ){ return vec->base; }
	return ( I8* )vec->base + ( vec->len - 1 - peek ) * vec->szof;
}