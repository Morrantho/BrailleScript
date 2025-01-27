struct vec
{
	i8* base;
	union { u32 len; u32 top; };
	u32 max;
	u32 szof;
};

void vec_init( vec* vec, u32 szof, u32 max );
void* vec_ptr( vec* vec, offset off );
void vec_reset( vec* vec );
void vec_grow( vec* vec );
u32 vec_push( vec* vec, void* value );
void* vec_pop( vec* vec );
offset vec_pops( vec* vec );
void vec_set( vec* vec, u32 idx, void* value );
void* vec_get( vec* vec, u32 idx );
offset vec_gets( vec* vec, u32 idx );
void* vec_peek( vec* vec );
offset vec_peeks( vec* vec );
void* vec_peekn( vec* vec, u32 idx );
offset vec_peekns( vec* vec, u32 idx );
void* vec_commit( vec* vec );
offset vec_commits( vec* vec );
void vec_free( vec* vec );
