#define KB( N ) ( ( N ) * 1024 )
#define MB( N ) ( KB( N ) * 1024 )
#define PAGE( N ) ( KB( 4 ) * N )
#define ALIGN_UP( X, P2 ) ( ( X + P2 - 1 ) & ~( P2 - 1 ) )
#define ALIGN_DOWN( X, P2 ) ( X & ~( P2 - 1 ) )

typedef struct Arena
{
	Void *base;
	U32 used;
	U32 max;
} Arena;

Arena *GetSrc( )
{
	static Arena src = { 0 };
	return &src;
}

Arena *GetStrings( )
{
	static Arena strings = { 0 };
	return &strings;
}

Void ArenaAlloc( Arena *arena, U32 max )
{
	max = ALIGN_UP( max, PAGE( 1 ) );
	arena->base = malloc( max );
	arena->used = 0;
	arena->max = max;
}

U32 ArenaPush( Arena *arena, U32 size, U32 p2align )
{
	U32 offset = ALIGN_UP( arena->used, p2align );
	if( offset + size > arena->max )
	{
		arena->max <<= 1;
		arena->base = realloc( arena->base, arena->max ); /* owie */
	}
	arena->used = offset + size;
	return offset;
}

U32 ArenaPop( Arena *arena, U32 bytes )
{
	if( bytes > arena->used ){ return 0; }
	U32 offset = arena->used;
	arena->used -= bytes;
	return offset;
}

Void *ArenaOff( Arena *arena, U32 offset )
{
	return ( I8* )arena->base + offset;
}

Void ArenaClear( Arena *arena )
{
	arena->used = 0;
}