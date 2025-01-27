struct bs
{
	heap heap;
	bslog log;
	lexer lexer;
	parser parser;
	compiler compiler;
};

void sig_on_sig( i32 sig );
void sig_init( );
void bs_run( bs* bs );
i32 bs_repl( bs* bs );
void bs_init( bs* bs, i8* file );
err_type bs_deinit( bs* bs, i32 nerrs );
i32 bs_start( bs* bs, i32 nargs, i8** args );
i32 main( i32 nargs, i8** args );