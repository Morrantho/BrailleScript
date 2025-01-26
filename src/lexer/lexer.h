#ifndef BS_LEXER_H
#define BS_LEXER_H

#define TK( T ) ( token ){ .type = T }
#define TKGEN( T, M, V ) ( token ){ .type = T, .M = V }

typedef struct lexer
{
	bslog* log;
	table* interns;
	i8* start;
	i8* end;
} lexer;

void lexer_init( lexer* lexer, bslog* log, heap* heap )
{
	lexer->interns = &heap->interns;
	lexer->log = log;
	lexer->start = lexer->end = heap->src.base;
}

void lexer_setsrc( lexer* lexer, heap* heap )
{
	lexer->start = lexer->end = heap->src.base;
}

lbl* lex_next( lexer* lexer, lbl** ascii )
{
	lexer->start = lexer->end;
	lexer->log->col++;
	return ascii[ *( u8* )lexer->end++ ];
}

lbl* lex_line( lexer* lexer, lbl* LEX )
{	/* \n */
	lexer->log->line++;
	lexer->log->col = 0;
	return LEX;
}

void lex_err( lexer* lexer )
{
	err_throw( err_tok, lexer->end - lexer->start, lexer->start );
}

token lex_eof( lexer* lexer )
{	/* \0 */
	lexer->log->col = 0;
	return TK( tk_eof );
}

token lex_not( lexer* lexer )
{	/* !, != */
	u8 res = '=' == *lexer->end;
	lexer->end += res;
	lexer->log->col += res;
	return TK( tk_not + res );	
}

token lex_str( lexer* lexer )
{	/* "any" */
	lexer->start++;
	while( *lexer->end && '"' != *lexer->end ){ lexer->end++; }
	u32 len = lexer->end - lexer->start;
	if( !*lexer->end )
	{
		log_err( lexer->log, err_str, len, lexer->start );
		return TK( tk_eof );
	}
	lexer->end++;
	lexer->log->col += len + 1;
	str* intern = table_put( lexer->interns, lexer->start, len );
	return TKGEN( tk_str, str, intern );
}

token lex_mod( lexer* lexer )
{	/* %, %= */
	u8 res = '=' == *lexer->end;
	lexer->end += res;
	lexer->log->col += res;
	return TK( tk_mod + res );	
}

token lex_band( lexer* lexer )
{	/* &, &=, && */
	u8 res = ( '=' == *lexer->end ) + ( '&' == *lexer->end ) * 2;
	lexer->end += res;
	lexer->log->col += res;
	return TK( tk_band + res );	
}

lbl* lex_comment( lexer* lexer, lbl* EOS, lbl* LEX )
{	/* # */
	while( *lexer->end && '\n' != *lexer->end ){ lexer->end++; }
	if( !*lexer->end ){ return EOS; }
	lexer->log->col = 0;
	lexer->log->line++;
	return LEX;
}

token lex_mul( lexer* lexer )
{	/* *, *=, ** */
	u8 res = ( '=' == *lexer->end ) + ( '*' == *lexer->end ) * 2;
	lexer->end += res;
	lexer->log->col += res;
	return TK( tk_mul + res );
}

token lex_add( lexer* lexer )
{	/* +, +=, ++ */
	u8 res = ( '=' == *lexer->end ) + ( '+' == *lexer->end ) * 2;
	lexer->end += res;
	lexer->log->col += res;
	return TK( tk_add + res );	
}

token lex_sub( lexer* lexer )
{	/* -, -=, -- */
	u8 res = ( '=' == *lexer->end ) + ( '-' == *lexer->end ) * 2;
	lexer->end += res;
	lexer->log->col += res;
	return TK( tk_sub + res );	
}

token lex_dot( lexer* lexer )
{	/* . .. .: .; */
	u8 res =  ( '.' == *lexer->end )
			+ ( ':' == *lexer->end ) * 2
			+ ( ';' == *lexer->end ) * 3;
	lexer->end += res;
	lexer->log->col += res;
	return TK( tk_dot + res );	
}

token lex_div( lexer* lexer )
{	/* /, /= */
	u8 res = ( '=' == *lexer->end );
	lexer->end += res;
	lexer->log->col += res;
	return TK( tk_div + res );
}

token lex_num( lexer* lexer, lbl** ascii, lbl* NUM )
{	/* 0-9.0-9 */
	while( NUM == ascii[ *( u8* )lexer->end ] ){ lexer->end++; }
	
	if( '.' != *lexer->end )
	{
		lexer->log->col += ( lexer->end - lexer->start ) - 1;
		i64 num = strtoll( lexer->start, &lexer->end, 10 );
		return TKGEN( tk_i64, i64, num );
	}

	if( NUM == ascii[ *( u8* )++lexer->end ] )
	{
		while( NUM == ascii[ *( u8* )lexer->end ] ) { lexer->end++; }
		lexer->log->col += ( lexer->end - lexer->start ) - 1;
		f64 num = strtod( lexer->start, &lexer->end );
		return TKGEN( tk_f64, f64, num );
	}

	log_err( lexer->log, err_f64, lexer->end - lexer->start, lexer->start );
	return TK( tk_eof );
}

token lex_colon( lexer* lexer )
{	/* : :: :. :> :>> */
	u8 res =  ( ':' == *lexer->end ) 			/* :: */
			+ ( '.' == *lexer->end ) * 2		/* :. */
			+ ( '>' == *lexer->end ) * 3		/* :> */
			+ ( '>' == *( lexer->end + 1 ) );	/* :>> */
	lexer->end += res;
	lexer->log->col += res;
	return TK( tk_col + res );
}

token lex_semi( lexer* lexer )
{	/* ; ;; ;. */
	u8 res = ( ';' == *lexer->end ) + ( '.' == *lexer->end ) * 2;
	lexer->end += res;
	lexer->log->col += res;
	return TK( tk_semi + res );
}

token lex_lt( lexer* lexer )
{	/* <, <=, <<, <<=, <<: */
	u8 res =  ( '=' == *lexer->end )				/* <= */
			+ ( '<' == *lexer->end ) * 2			/* << */
			+ ( '=' == *( lexer->end + 1 ) )		/* <<= */
			+ ( ':' == *( lexer->end + 1 ) ) * 2;	/* <<: */
	lexer->end += res;
	lexer->log->col += res;
	return TK( tk_lt + res );
}

token lex_eq( lexer* lexer )
{	/* =, == */
	u8 res = '=' == *lexer->end;
	lexer->end += res;
	lexer->log->col += res;
	return TK( tk_eq + res );	
}

token lex_gt( lexer* lexer )
{	/* >, >=, >>, >>= */
	u8 res =  ( '=' == *lexer->end )
			+ ( '>' == *lexer->end ) * 2
			+ ( '=' == *( lexer->end + 1 ) );
	lexer->end += res;
	lexer->log->col += res;
	return TK( tk_gt + res );	
}

token lex_id( lexer* lexer, lbl** ascii, lbl* ID, lbl* NUM )
{	/* A-Za-z0-9_ */
	while( ID  == ascii[ *( u8* )lexer->end ]
		|| NUM == ascii[ *( u8* )lexer->end ] ){ lexer->end++; }
	u32 len = lexer->end - lexer->start;
	lexer->log->col += len - 1;
	str* intern = table_put( lexer->interns, lexer->start, len );
	return TKGEN( tk_id, str, intern );
}

token lex_bxor( lexer* lexer )
{	/* ^, ^= */
	u8 res = ( '=' == *lexer->end );
	lexer->end += res;
	lexer->log->col += res;
	return TK( tk_bxor + res );
}

token lex_bor( lexer* lexer )
{	/* |, |=, || */
	u8 res = ( '=' == *lexer->end ) + ( '|' == *lexer->end );
	lexer->end += res;
	lexer->log->col += res;
	return TK( tk_bor + res );
}

token lex( lexer* lexer )
{
	static void* ascii[ ] = { ASCII( X_ASCII_LBL ) };
	LEX: goto *lex_next( lexer, ascii ); /* dispatch */
	LINE: goto *lex_line( lexer, &&LEX ); /* \n */
	ERR: lex_err( lexer );
	EOS: return lex_eof( lexer ); /* \0 */
	NOT: return lex_not( lexer ); /* !, != */
	STR: return lex_str( lexer ); /* "any" */
	MOD: return lex_mod( lexer ); /* %, %= */
	BAND: return lex_band( lexer ); /* &, &=, && */
	COMMENT: goto *lex_comment( lexer, &&EOS, &&LEX ); /* # */
	LP: return TK( tk_lp ); /* ( */
	RP: return TK( tk_rp ); /* ) */
	MUL: return lex_mul( lexer ); /* *, *=, ** */
	ADD: return lex_add( lexer ); /* +, +=, ++ */
	COM: return TK( tk_com ); /* , */
	SUB: return lex_sub( lexer ); /* -, -=, -- */
	DOT: return lex_dot( lexer ); /* . .. .: .; */
	DIV: return lex_div( lexer );  /* /, /= */
	NUM: return lex_num( lexer, ascii, &&NUM );
	COL: return lex_colon( lexer ); /* : :: :. */
	SEMI: return lex_semi( lexer ); /* ; ;; ;. */
	LT: return lex_lt( lexer ); /* <, <=, <<, <<= */
	EQ: return lex_eq( lexer ); /* =, == */
	GT: return lex_gt( lexer ); /* >, >=, >>, >>= */
	RET: return TK( tk_ret ); /* @ */
	ID: return lex_id( lexer, ascii, &&ID, &&NUM ); /* A-Za-z0-9_ */
	LS: return TK( tk_ls ); /* [ */
	RS: return TK( tk_rs ); /* ] */
	BXOR: return lex_bxor( lexer ); /* ^, ^= */
	LC: return TK( tk_lc ); /* { */
	BOR: return lex_bor( lexer ); /* |, |=, || */
	RC: return TK( tk_rc ); /* } */
	BNOT: return TK( tk_bnot ); /* ~ */
}

#endif