#ifndef BS_OFFSET_H
#define BS_OFFSET_H

typedef struct offset
{
	union { u32 idx; u32 start; };
	union { u32 scl; u32 szof; };
} offset;

offset offset_init( u32 idx, u32 scl )
{
	return ( offset ){ .idx = idx, .scl = scl };
}

void* offset_ptr( void* base, offset off )
{
	return base + ( off.idx * off.scl );
}

#endif
