struct parser
{
	token token;
	lexer* lexer;
	vec* states;
	vec* precs;
	vec* irs;
	compiler* compiler;
	bslog* log;
};

void parser_init( parser* parser, heap* heap, lexer* lexer, compiler* compiler );
void parse_match( parser* parser, token_type type );
void parse_ret( parser* parser );
void parse_if( parser* parser );
void parse_for( parser* parser );
void parse_args( parser* parser, i64 nargs );
void parse_fn( parser* parser, str* name );
void parse_fn_body( parser* parser );
void parse_fn_end( parser* parser );
void parse_while( parser* parser );
void parse_do( parser* parser );
void parse_assign( parser* parser );
void parse_unary( parser* parser );
void parse_unary_end( parser* parser );
void parse_binary( parser* parser );
void parse_binary_end( parser* parser );
void parse_group( parser* parser );
void parse_group_end( parser* parser );
void parse_i64( parser* parser );
void parse_f64( parser* parser );
void parse_str( parser* parser );
void parse_ref( parser* parser );
void parse_expr( parser* parser );
void parse_stmt( parser* parser );
void parse( parser* parser );
