void log_init( bslog* log, heap* heap, i8* file )
{
	log->file = file;
	log->logstrs = &heap->logstrs;
	log->logs = &heap->logs;
	log->line = 1;
	log->col = 0;
}

void log_reset( bslog* log )
{
	log->logstrs->used = 0;
	log->logs->len = 0;
}

u32 log_err( bslog* log, err_type type, ... )
{
	const err_info* info = err_get( type );
	u32 szof = sizeof( err ) + LOG_BUF + 1;
	u32 offset = arena_alloc( log->logstrs, szof, 8 );
	err* e = ( err* )log->logstrs->base + offset;
	e->name = info->name;
	e->file = log->file;
	e->line = log->line;
	e->col = log->col;

	i8* buf = ( i8* )( e + 1 );
	va_list args;
	va_start( args, type );
	i32 bytes = vsnprintf( buf, LOG_BUF, info->desc, args );
	va_end( args );
	buf[ bytes ] = '\0';

	return vec_push( log->logs, &offset );
}

void log_all( bslog* log )
{
	for( u32 i = 0; i < log->logs->len; i++ )
	{
		u32 offset = *( u32* )( log->logs->base + i * sizeof( u32 ) );
		err* e = ( err* )log->logstrs->base + offset;
		i8* desc = ( i8* )( e + 1 );

		fprintf( stderr, "%s: %d:%d | %s",
			e->file,
			e->line,
			e->col,
			desc
		);
	}
	log_reset( log );
}
