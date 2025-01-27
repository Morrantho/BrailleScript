offset offset_init( u32 idx, u32 scl )
{
	return ( offset ){ .idx = idx, .scl = scl };
}

void* offset_ptr( void* base, offset off )
{
	return base + ( off.idx * off.scl );
}
