void parser_init( parser* parser, heap* heap, lexer* lexer, compiler* compiler )
{
	parser->lexer = lexer;
	parser->states = &heap->pstates;
	parser->precs = &heap->pprecs;
	parser->irs = &heap->pirs;
	parser->compiler = compiler;
	parser->log = lexer->log;
}

void parse_match( parser* parser, token_type type )
{
	if( type != parser->token.type )
	{
		const i8* exp = token_str( type );
		const i8* got = token_str( parser->token.type );
		log_err( parser->log, err_match, exp, got );
	}
	parser->token = lex( parser->lexer );
}

void parse_ret( parser* parser )
{
	parse_match( parser, tk_ret );
}

void parse_if( parser* parser )
{
	parse_match( parser, tk_if );
}

void parse_for( parser* parser )
{
	parse_match( parser, tk_for );
}

void parse_args( parser* parser, i64 nargs )
{
	while( tk_id == parser->token.type )
	{
		ir_push( parser, ir_arg, value_str, parser->token.str );
		parse_match( parser, tk_id );
		if( tk_com != parser->token.type ){ return; }
		parse_match( parser, tk_com );
		nargs++;
		if( tk_id != parser->token.type )
		{
			log_err( parser->log, err_args );
			return;
		}
	}
	ir_push( parser, ir_arg, value_i64, &nargs );
}

void parse_fn( parser* parser, str* name )
{
	parse_match( parser, tk_lp );
	ir_push( parser, ir_fn, value_str, name );
	parse_args( parser, 0 );
	parse_match( parser, tk_rp );
	/* body */
	pstate_push( parser, ps_fn_end );
	pstate_push( parser, ps_fn_body );
	pstate_push( parser, ps_stmt );
}

void parse_fn_body( parser* parser )
{
	if( !parser->token.type || tk_end == parser->token.type ){ return; }
	pstate_push( parser, ps_fn_body );
	pstate_push( parser, ps_stmt );
}

void parse_fn_end( parser* parser )
{
	parse_match( parser, tk_end );
	// compile_fn();
}

void parse_while( parser* parser )
{
	parse_match( parser, tk_while );
}

void parse_do( parser* parser )
{
	parse_match( parser, tk_do );
	pstate_push( parser, ps_stmt );
	parse_match( parser, tk_while );
	parse_match( parser, tk_end );
}

void parse_assign( parser* parser )
{	/* x:123, add:( */
	str* name = parser->token.str;
	parse_match( parser, tk_id );
	parse_match( parser, tk_col );
	if( tk_lp == parser->token.type ){ return parse_fn( parser, name ); }
	/* TODO: push local + emit mov */
	pstate_push( parser, ps_expr );
}

void parse_unary( parser* parser )
{
	ir* unary = vec_commit( parser->irs );
	unary->value.i64 = tk_to_op( parser->token.type );
	parse_match( parser, parser->token.type );  /* consume operator */
	pstate_push( parser, ps_unary_end );
	pstate_push( parser, ps_expr );
}

void parse_unary_end( parser* parser )
{
	unary_compile( parser->compiler, parser );
}

void parse_binary( parser* parser )
{
	ir* binary = vec_commit( parser->irs );
	binary->value.i64 = tk_to_op( parser->token.type );
	parse_match( parser, parser->token.type ); /* consume operator */
	pstate_push( parser, ps_binary_end );
	pstate_push( parser, ps_expr );
}

void parse_binary_end( parser* parser )
{
	binary_compile( parser->compiler, parser );
}

void parse_group( parser* parser )
{
	parse_match( parser, tk_lp );
	pstate_push( parser, ps_group_end );
	pstate_push( parser, ps_expr );
}

void parse_group_end( parser* parser )
{
	parse_match( parser, tk_rp );
}

void parse_i64( parser* parser )
{
	ir_push( parser, ir_const, value_i64, &parser->token.i64 );
	parse_match( parser, tk_i64 );
}

void parse_f64( parser* parser )
{
	ir_push( parser, ir_const, value_f64, &parser->token.f64 );
	parse_match( parser, tk_f64 );
}

void parse_str( parser* parser )
{
	ir_push( parser, ir_const, value_str, parser->token.str );
	parse_match( parser, tk_str );
}

void parse_ref( parser* parser )
{
	ir_push( parser, ir_ref, value_str, parser->token.str );
	parse_match( parser, tk_id );
}

void parse_expr( parser* parser )
{
	static const parse_rule exprs[ tk_n ] = { EXPRS( X_EXPR_RULE ) };
	prec_push( parser, prec_none );
	const parse_rule* rule = &exprs[ parser->token.type ];
	goto *rule->nud;
	/* NUD: */
		UNARY: return parse_unary( parser ); /* defer */
		GROUP: return parse_group( parser ); /* defer */
		I64: parse_i64( parser ); goto LED;
		F64: parse_f64( parser ); goto LED;
		STR: parse_str( parser ); goto LED;
		REF: parse_ref( parser ); /* fallthrough */
	LED:
		rule = &exprs[ parser->token.type ];
		if( rule->prec <= prec_peek( parser ) ){ goto DONE; }
		prec_push( parser, rule->prec );
		goto *rule->led;
		BINARY: parse_binary( parser ); goto LED;
	ERR:
		err_throw( err_match, token_str( parser->token.type ) );
	EOS:
	DONE: prec_pop( parser );
}

void parse_stmt( parser* parser )
{
	static const lbl* stmts[ tk_n ] = { STMTS( X_STMT_LBL ) };
	goto *stmts[ parser->token.type ];
	RET: return parse_ret( parser );
	IF: return parse_if( parser );
	FOR: return parse_for( parser );
	WHILE: return parse_while( parser );
	DO: return parse_do( parser );
	ASSIGN: return parse_assign( parser );
	EXPR: return parse_expr( parser );
}

/* DEFERRED states only. */
void parse( parser* parser )
{
	static const lbl* states[ ps_n ] = { PARSE_STATES( ps_, X_PS_LBL ) };
	parser->token = lex( parser->lexer );
	goto STMT;
	while( parser->states->len )
	{
		parse_state state = pstate_pop( parser );
		goto *states[ state ];
		ERR: return;
		STMT: parse_stmt( parser ); continue;
		EXPR: parse_expr( parser ); continue;
		UNARY_END: parse_unary_end( parser ); continue;
		GROUP_END: parse_group_end( parser ); continue;
		BINARY_END: parse_binary_end( parser ); continue;
		FN_BODY: parse_fn_body( parser ); continue;
		FN_END: parse_fn_end( parser ); continue;
	}
	parser->states->len = 0;
	parser->precs->len = 0;
	parser->irs->len = 0;
}
