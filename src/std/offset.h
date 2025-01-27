struct offset
{
	union { u32 idx; u32 start; };
	union { u32 scl; u32 szof; };
};

offset offset_init( u32 idx, u32 scl );
void* offset_ptr( void* base, offset off );
