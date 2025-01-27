struct entry
{
	union { str* key; str* name; };
	value* value;
	u32 idx; /* hashed index / var index */
};

struct map
{
	entry* base;
	u32 len;
	u32 max;
};

void map_init( map* map );