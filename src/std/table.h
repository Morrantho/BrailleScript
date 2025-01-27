#define TABLE_LOAD 0.65

struct table
{
	u32* base;
	arena* strings;
	u32 len;
	u32 max;
};

struct table_res
{
	str* found; /* str */
	u32 idx;
};

void table_init( table* table, arena* strings, u32 max );
table_res table_find( table* table, i8* src, u32 len, u32 hash );
void table_reput( table* table, u32 ooff );
void table_grow( table* table );
str* table_put( table* table, i8* src, u32 len );
