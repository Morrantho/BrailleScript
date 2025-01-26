#include "bs.h"

void sig_on_sig( i32 sig )
{
	longjmp( err_jmp, sig ^ sig ); /* stop warning me */
}

void sig_init( )
{
	static u8 sigs[ ] = { SIGINT, SIGSTOP, SIGTSTP, SIGKILL };
	for( u8 i = 0; i < sizeof( sigs ) / sizeof( sigs[ 0 ] ); i++ )
	{
		signal( sigs[ i ], sig_on_sig );
	}
}

void bs_run( bs* bs )
{
	lexer_setsrc( &bs->lexer, &bs->heap );
	parse( &bs->parser );
	log_all( &bs->log );
}

i32 bs_repl( bs* bs )
{
	arena* src = &bs->heap.src;
	ir* evald = ( ir* )bs->heap.pirs.base;
	for( ;; )
	{
		printf( "$ " );
		src->base = fgets( src->base, src->max, stdin );
		bs_run( bs );
		ir_logeval( evald );
	}
	return EXIT_SUCCESS;
}

void bs_init( bs* bs, i8* file )
{
	sig_init( );
	heap_init( &bs->heap );
	log_init( &bs->log, &bs->heap, file );
	lexer_init( &bs->lexer, &bs->log, &bs->heap );
	parser_init( &bs->parser, &bs->heap, &bs->lexer, &bs->compiler );
	compiler_init( &bs->compiler, &bs->heap, &bs->parser );
}

err_type bs_deinit( bs* bs, i32 nerrs )
{
	heap_deinit( &bs->heap );
	return nerrs; /* non-zero exit code if errors. */
}

i32 bs_start( bs* bs, i32 nargs, i8** args )
{
	if( nargs != 2 )
	{
		bs_init( bs, "Repl" );
		return bs_repl( bs );
	}
	bs_init( bs, args[ 1 ] );
	io_read( &bs->heap.src, args[ 1 ] );
	bs_run( bs );
	return bs->log.logs->len;
}

i32 main( i32 nargs, i8** args )
{
	bs bs = { 0 };
	i32 err = setjmp( err_jmp );
	if( err ){ return bs_deinit( &bs, 1 ); }
	i32 nerrs = bs_start( &bs, nargs, args );
	return bs_deinit( &bs, nerrs );
}