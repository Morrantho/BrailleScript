const i8* token_str( token_type type )
{
	static const i8* names[ tk_n ] = { TOKENS( tk_, X_TOKEN_STR ) };
	return names[ type ];
}

i32 token_log( token* token )
{
	static const void* types[ tk_n ] =
	{
		[ 0 ... tk_n - 1 ] = &&LBL_DEFAULT,
		[ tk_i64 ] = &&LBL_I64,
		[ tk_f64 ] = &&LBL_F64,
		[ tk_str ] = &&LBL_STR,
	};
	const i8* type = token_str( token->type );
	goto *types[ token->type ];
LBL_DEFAULT:
	return printf( "%s\n", type );
LBL_I64:
	return printf( "%s: %ld\n", type, token->i64 );
LBL_F64:
	return printf( "%s: %f\n", type, token->f64 );
LBL_STR:
	return printf( "%s: %s\n", type, ( i8* )( token->str + 1 ) );
}
