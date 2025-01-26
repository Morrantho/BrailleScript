#ifndef BS_ARENA_H
#define BS_ARENA_H

typedef struct arena
{
	i8* base;
	union { u32 used; u32 len; };
	u32 max;
} arena;

void arena_init( arena* arena, u32 max )
{
	arena->base = malloc( max );
	arena->max = max;
	arena->used = 0;
}

void arena_reset( arena* arena )
{
	arena->used = 0;
}

u32 arena_align( u32 used, u32 alignment )
{
	u32 mask = alignment - 1;
	return ( used + mask ) & ~mask;
}

void arena_grow( arena* arena, u32 desired )
{
	while( arena->max < desired ){ arena->max <<= 1; }
	arena->base = realloc( arena->base, arena->max );
}

u32 arena_alloc( arena* arena, u32 size, u32 alignment )
{
	u32 offset = arena_align( arena->used, alignment );
	u32 end = offset + size;
	if( end > arena->max ){ arena_grow( arena, end ); }
	arena->used = end;
	return offset;
}

void* arena_ptr( arena* arena, u32 offset )
{
	return arena->base + offset;
}

#endif