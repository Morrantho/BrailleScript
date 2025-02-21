static ParseRule rules[ ] =
{
	[ TK_EOS ] = { &&EOS, &&EOS, PREC_NONE },

	[ TK_NOT ] = { &&UNARY, &&ERR, PREC_NOT },
	[ TK_NEQ ] = { &&ERR, &&BINARY, PREC_EQNEQ },

	[ TK_BNOT ] = { &&UNARY, &&ERR, PREC_NOT },

	[ TK_ADD ] = { &&UNARY, &&BINARY, PREC_TERM },
	[ TK_ADDEQ ] = { &&ERR, &&BINARY, PREC_TERMEQ },
	[ TK_ADDADD ] =	{ &&UNARY, &&ERR, PREC_PRETERM },

	[ TK_SUB ] = { &&UNARY, &&BINARY, PREC_TERM },
	[ TK_SUBEQ ] = { &&ERR, &&BINARY, PREC_TERMEQ },
	[ TK_SUBSUB ] = { &&UNARY, &&ERR, PREC_PRETERM },

	[ TK_MUL ] = { &&ERR, &&BINARY, PREC_FACT },
	[ TK_MULEQ ] = { &&ERR, &&BINARY, PREC_FACTEQ },
	[ TK_POW ] = { &&ERR, &&BINARY, PREC_POW },
	[ TK_POWEQ ] = { &&ERR, &&BINARY, PREC_POWEQ },

	[ TK_DIV ] = { &&ERR, &&BINARY, PREC_FACT },
	[ TK_DIVEQ ] = { &&ERR, &&BINARY, PREC_FACTEQ },
	
	[ TK_MOD ] = { &&ERR, &&BINARY, PREC_FACT },
	[ TK_MODEQ ] = { &&ERR, &&BINARY, PREC_FACTEQ },

	[ TK_BAND ] = { &&ERR, &&BINARY, PREC_BAND },
	[ TK_BANDEQ ] = { &&ERR, &&BINARY, PREC_BITEQ },
	[ TK_AND ] = { &&ERR, &&BINARY, PREC_AND },

	[ TK_BOR ] = { &&ERR, &&BINARY, PREC_BOR },
	[ TK_BOREQ ] = { &&ERR, &&BINARY, PREC_BITEQ },
	[ TK_OR ] = { &&ERR, &&BINARY, PREC_OR },

	[ TK_BXOR ] = { &&ERR, &&BINARY, PREC_BXOR },
	[ TK_BXOREQ ] = { &&ERR, &&BINARY, PREC_BITEQ },

	[ TK_EQ ] = { &&ERR, &&ERR, PREC_NONE }, /* Not the assignment op */
	[ TK_EQEQ ] = { &&ERR, &&BINARY, PREC_EQNEQ },

	[ TK_LT ] = { &&ERR, &&BINARY, PREC_GTLT },
	[ TK_LE ] = { &&ERR, &&BINARY, PREC_GTLT },
	[ TK_LSH ] = { &&ERR, &&BINARY, PREC_SH },
	[ TK_LSHEQ ] = { &&ERR, &&BINARY, PREC_SHEQ },

	[ TK_GT ] = { &&ERR, &&BINARY, PREC_GTLT },
	[ TK_GE ] = { &&ERR, &&BINARY, PREC_GTLT },
	[ TK_RSH ] = { &&ERR, &&BINARY, PREC_SH },
	[ TK_RSHEQ ] = { &&ERR, &&BINARY, PREC_SHEQ },

	[ TK_LP ] =	{ &&GROUP, &&CALL, PREC_CALL },
	[ TK_RP ] = { &&ERR, &&ERR, PREC_NONE },
	[ TK_LS ] = { &&ERR, &&ERR, PREC_INDEX },
	[ TK_RS ] = { &&ERR, &&ERR, PREC_NONE },
	[ TK_LC ] = { &&ERR, &&ERR, PREC_NONE },
	[ TK_RC ] = { &&ERR, &&ERR, PREC_NONE },

	[ TK_DOT ] = { &&ERR, &&ERR, PREC_MEMBER },
	[ TK_IF ] = { &&ERR, &&ERR, PREC_NONE },
	[ TK_FOR ] = { &&ERR, &&ERR, PREC_NONE },
	[ TK_ELSE ] = { &&ERR, &&ERR, PREC_NONE },

	[ TK_SEMI ] = { &&ERR, &&ERR, PREC_NONE },
	[ TK_DO ] = { &&ERR, &&ERR, PREC_NONE },
	[ TK_WHILE ] = { &&ERR, &&ERR, PREC_NONE },

	[ TK_COLON ] = { &&ERR, &&BINARY, PREC_EQ }, /* for folding only */
	[ TK_THEN ] = { &&ERR, &&ERR, PREC_NONE },
	[ TK_END ] = { &&ERR, &&ERR, PREC_NONE },

	[ TK_COMMA ] = { &&ERR, &&ERR, PREC_LIST },
	[ TK_RET ] = { &&ERR, &&ERR, PREC_NONE },

	[ TK_I64 ] = { &&I64, &&ERR, PREC_NONE },
	[ TK_F64 ] = { &&F64, &&ERR, PREC_NONE },
	[ TK_STR ] = { &&STR, &&ERR, PREC_NONE },
	[ TK_ID ] = { &&REF, &&ERR, PREC_NONE }
};