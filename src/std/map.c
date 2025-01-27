struct entry
{
	union { str* key; str* name; };
	value value;
};

struct map
{
	entry* base;
	u32 len;
	u32 max;
};
