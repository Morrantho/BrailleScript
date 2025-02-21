Void OnSig( I32 sig )
{
	longjmp( *GetJmp( ), EXIT_SUCCESS );
}

Void Init( )
{
	MemAlloc( );
	LexerInit( );
	ParserInit( );
	CompilerInit( );
	signal( SIGINT, OnSig );
	signal( SIGTSTP, OnSig );
	signal( SIGKILL, OnSig );
}

Void Run( )
{
	Vec *code = GetCode( );
	U32 clen = code->len;
	LexReinit( ( I8* )GetSrc( )->base );
	Parse( );
	if( code->len == clen ){ return; }
	OpLog( VecPeek( code ) );
}

I32 Repl( )
{
	Init( );
	Arena *src = GetSrc( );
	I8 *line = ( I8* )src->base;
	for( ;; )
	{
		printf( "$ " );
		line = fgets( line, src->max, stdin );
		Run( );
	}
	return EXIT_SUCCESS;
}

I32 Load( I8 *file )
{
	Init( );
	IoRead( GetSrc( ), file );
	Run( );
	return EXIT_SUCCESS;
}

I32 Deinit( I32 err )
{
	MemDealloc( );
	return err;
}

I32 main( I32 nargs, I8 **args )
{
	I32 res = setjmp( *GetJmp( ) );
	if( res ){ return Deinit( res ); }
	if( nargs == 1 ){ return Repl( ); }
	return Load( args[ 1 ] );
}