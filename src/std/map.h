typedef struct Entry
{ /* Used in GetGlobals() and GetLocals() vectors. */
	union{ String *key; String *name; };
	Value value;
} Entry;
typedef Entry Var;

typedef struct Map
{ /* These are for user-defined hashmaps in code. */
	Entry *base;
	U32 len;
	U32 max;
} Map;

Void MapGrow( Map *map );
Void MapPut( Map *map, String *key, Value value );

Void MapAlloc( Map *map, U32 max )
{
	map->base = calloc( max, sizeof( Entry ) );
	map->len = 0;
	map->max = max;
}

Void MapGrow( Map *map )
{
	Entry *entries = map->base;
	U32 old_max = map->max;
	MapAlloc( map, map->max << 1 );
	for( U32 i = 0; i < old_max; i++ )
	{
		Entry *entry = &entries[ i ];
		if( !entry->key ){ continue; }
		MapPut( map, entry->key, entry->value );
	}
	free( entries );
}

Entry *MapGet( Map *map, String *key )
{
	U32 idx = key->hash & ( map->max - 1 );
	for( ;; idx = ( idx + 1 ) & ( map->max - 1 ) )
	{
		Entry *entry = &map->base[ idx ];
		if( !entry->key ){ return entry; }
		if( entry->key == key ){ return entry; }
	}
	return NULL;
}

Void MapPut( Map *map, String *key, Value value )
{
	if( map->len > map->max ){ MapGrow( map ); }
	Entry *entry = MapGet( map, key );
	map->len += entry->key == NULL;
	entry->key = key;
	entry->value = value;
}

Void MapDel( Map *map, String *key )
{
	Entry *entry = MapGet( map, key );
	entry->key = NULL;
}