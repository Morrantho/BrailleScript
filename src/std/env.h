typedef struct Evar
{ /* Same as Var, but smaller for caching. sizeof = 8 */
	U32 offset; /* strings arena offset. we compare this for lookups, not ptrs */
	U32 idx; /* globals index */
} Evar;

typedef struct Env
{
	Evar *base;
	U32 len;
	U32 max;
} Env;

Void EnvPut( Env *env, String *name, U32 idx );

Env *GetEnv( )
{
	static Env env = { 0 };
	return &env;
}

Void EnvAlloc( Env *env, U32 max )
{
	env->base = calloc( max, sizeof( Evar ) );
	env->len = 0;
	env->max = max;
}

Void EnvGrow( Env *env )
{
	Evar *vars = env->base;
	U32 old_max = env->max;
	Arena *strings = GetStrings( );
	EnvAlloc( env, env->max << 1 );
	for( U32 i = 0; i < old_max; i++ )
	{
		Evar *var = &vars[ i ];
		if( !var->idx ){ continue; } /* skip empties */
		String *str = ArenaOff( strings, var->offset );
		EnvPut( env, str, var->idx );
	}
	free( vars );
}

Var *EvarToVar( Evar *evar )
{
	return VecGet( GetGlobals( ), evar->idx );
}

Evar *EnvGet( Env *env, String *name )
{
	U32 idx = name->hash & ( env->max - 1 );
	for( ;; idx = ( idx + 1 ) & ( env->max - 1 ) )
	{
		Evar *evar = &env->base[ idx ];
		if( !evar->idx ){ return evar; }
		Var *var = EvarToVar( evar );
		if( var->name == name ){ return evar; }
	}
	I8 *cstr = ArenaOff( GetStrings( ), name->offset );
	Throw( "Failed to find Evar: %s in Env.\n", cstr );
	return NULL;
}

Void EnvPut( Env *env, String *name, U32 idx )
{
	if( env->len > env->max ){ EnvGrow( env ); }
	Evar *var = EnvGet( env, name );
	env->len += var->idx == 0;
	var->offset = name->offset;
	var->idx = idx;
}

Void EnvDel( Env *env, String *name )
{
	Evar *var = EnvGet( env, name );
	var->idx = 0;
}