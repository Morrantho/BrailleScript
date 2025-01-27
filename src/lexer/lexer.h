#define TK( T ) ( token ){ .type = T }
#define TKGEN( T, M, V ) ( token ){ .type = T, .M = V }

struct lexer
{
	bslog* log;
	table* interns;
	i8* start;
	i8* end;
};

void lexer_init( lexer* lexer, bslog* log, heap* heap );
void lexer_setsrc( lexer* lexer, heap* heap );
lbl* lex_next( lexer* lexer, lbl** ascii );
lbl* lex_line( lexer* lexer, lbl* LEX );
void lex_err( lexer* lexer );
token lex_eof( lexer* lexer );
token lex_not( lexer* lexer );
token lex_str( lexer* lexer );
token lex_mod( lexer* lexer );
token lex_band( lexer* lexer );
lbl* lex_comment( lexer* lexer, lbl* EOS, lbl* LEX );
token lex_mul( lexer* lexer );
token lex_add( lexer* lexer );
token lex_sub( lexer* lexer );
token lex_dot( lexer* lexer );
token lex_div( lexer* lexer );
token lex_num( lexer* lexer, lbl** ascii, lbl* NUM );
token lex_colon( lexer* lexer );
token lex_semi( lexer* lexer );
token lex_lt( lexer* lexer );
token lex_eq( lexer* lexer );
token lex_gt( lexer* lexer );
token lex_id( lexer* lexer, lbl** ascii, lbl* ID, lbl* NUM );
token lex_bxor( lexer* lexer );
token lex_bor( lexer* lexer );
token lex( lexer* lexer );
