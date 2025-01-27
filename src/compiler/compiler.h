struct compiler
{
	parser* parser;
	vec* consts; /* vec< value > */
	bslog* log;
};

void compiler_init( compiler* compiler, heap* heap, parser* parser );
u32 const_push( compiler* compiler, value* value );
value* const_get( compiler* compiler, u32 idx );
void compile_unary( compiler* compiler, parser* parser );
void compile_binary( compiler* compiler, parser* parser );
