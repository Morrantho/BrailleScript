#ifndef BS_MAP_H
#define BS_MAP_H

typedef struct entry
{
	union { str* key; str* name; };
	value value;
} entry;

typedef struct map
{
	entry* base;
	u32 len;
	u32 max;
} map;

typedef entry var;
typedef map env;

#endif