enum token_type
{
	TOKENS( tk_, X_TOKEN_ENUM )
	tk_n
};

struct token
{
	token_type type;
	union
	{
		i64 i64;
		f64 f64;
		str* str;
	};
};

const i8* token_str( token_type type );
i32 token_log( token* token );
