#ifndef BS_COMPILER_H
#define BS_COMPILER_H

typedef struct compiler
{
	parser* parser;
	vec* consts; /* vec< value > */
	bslog* log;
} compiler;

void compiler_init( compiler* compiler, heap* heap, parser* parser )
{
	compiler->parser = parser;
	compiler->consts = &heap->consts;
	compiler->log = parser->log;
}

u32 const_push( compiler* compiler, value* value )
{
	return vec_push( compiler->consts, value );
}

value* const_get( compiler* compiler, u32 idx )
{
	return ( value* )vec_get( compiler->consts, idx );
}

void compile_unary( compiler* compiler, parser* parser )
{
	ir* rhs = vec_pop( parser->irs );
	ir* op = vec_pop( parser->irs );
	ir* out = vec_commit( parser->irs );
	if( una_foldable( rhs ) ){ return una_fold( out, op, rhs ); }
	/* emit here */
}

void compile_binary( compiler* compiler, parser* parser )
{
	// static void* ops[ tk_n ][ tk_n ] = { };
	ir* rhs = vec_pop( parser->irs );
	ir* op = vec_pop( parser->irs );
	ir* lhs = vec_pop( parser->irs );
	ir* out = vec_commit( parser->irs );
	if( bin_foldable( lhs, rhs ) ){ return bin_fold( out, lhs, op, rhs ); }
	/* emit here. write to out if needed. */
}

#endif
