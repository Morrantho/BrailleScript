struct str
{	/* Add 1 to get its cstr: u8* cstr = ( u8* )( str + 1 ); */
	u32 len;
	u32 hash;
	// u8 flags;
};

struct str_res
{
	str* str;
	u32 offset;
};

u32 str_hash( i8* cstr, u32 len );
str_res str_alloc( arena* strings, i8* src, u32 len, u32 hash );
