Void MemAlloc( )
{
	ArenaAlloc( GetSrc( ), KB( 32 ) ); /* Arena< I8 > */
	ArenaAlloc( GetStrings( ), KB( 16 ) ); /* Arena< I8 > */
	TableAlloc( GetInterns( ), GetStrings( ), 256 ); /* Table< String > */
	VecAlloc( GetConsts( ), 256, sizeof( Value ) ); /* Vec< Value > */
	VecAlloc( GetLocals( ), 256, sizeof( Var ) ); /* Vec< Var > */
	VecAlloc( GetGlobals( ), 256, sizeof( Var ) ); /* Vec< Var > */
	EnvAlloc( GetEnv( ), 256 ); /* Env< Evar: 8 > */
	VecAlloc( GetCode( ), 256, sizeof( Op ) ); /* Vec< Op > */
	VecAlloc( GetFuncs( ), 128, sizeof( Func ) ); /* Vec< Func > */
}

Void MemDealloc( )
{
	free( GetFuncs( )->base );
	free( GetCode( )->base );
	free( GetEnv( )->base );
	free( GetGlobals( )->base );
	free( GetLocals( )->base );
	free( GetConsts( )->base );
	free( GetInterns( )->base );
	free( GetStrings( )->base );
	free( GetSrc( )->base );
}