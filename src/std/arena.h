struct arena
{
	i8* base;
	union { u32 used; u32 len; };
	u32 max;
};

void arena_init( arena* arena, u32 max );
void arena_reset( arena* arena );
u32 arena_align( u32 used, u32 alignment );
void arena_grow( arena* arena, u32 desired );
u32 arena_alloc( arena* arena, u32 size, u32 alignment );
void* arena_ptr( arena* arena, u32 offset );
