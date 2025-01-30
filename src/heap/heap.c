void heap_init( heap* heap )
{
	arena_init( &heap->logstrs, KB( 128 ) );
	vec_init( &heap->logs, sizeof( u32 ), 256 );
	arena_init( &heap->src, MB( 2 ) );
	arena_init( &heap->strings, KB( 256 ) );
	table_init( &heap->interns, &heap->strings, 512 );
	vec_init( &heap->pstates, sizeof( parse_state ), 512 );
	vec_init( &heap->pprecs, sizeof( prec ), 256 );
	vec_init( &heap->pirs, sizeof( ir ), KB( 64 ) / sizeof( ir ) );
	vec_init( &heap->consts, sizeof( value ), KB( 64 ) / sizeof( value ) );
	vec_init( &heap->vars, sizeof( var ), 1024 );
	vec_init( &heap->ops, sizeof( op ), 4096 );
	vec_init( &heap->funcs, sizeof( func ), 256 );
}

void heap_deinit( heap* heap )
{
	free( heap->funcs.base );
	free( heap->ops.base );
	free( heap->vars.base );
	free( heap->consts.base );
	free( heap->pirs.base );
	free( heap->pprecs.base );
	free( heap->pstates.base );
	free( heap->interns.base );
	free( heap->strings.base );
	free( heap->src.base );
	free( heap->logs.base );
	free( heap->logstrs.base );
}
