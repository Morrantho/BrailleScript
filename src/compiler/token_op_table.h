static OpCode token_ops[ TK_N ] =
{
	[ 0 ... TK_N - 1 ] = OP_NOP, /* Default no op */
	[ TK_NOT ] = OP_NOT,
	[ TK_NEQ ] = OP_NEQ,
	[ TK_BNOT ] = OP_BNOT,
	[ TK_ADD ] = OP_ADD,
	[ TK_ADDEQ ] = OP_ADDEQ,
	[ TK_ADDADD ] = OP_PREINC,
	[ TK_SUB ] = OP_SUB,
	[ TK_SUBEQ ] = OP_SUBEQ,
	[ TK_SUBSUB ] = OP_PREDEC,
	[ TK_MUL ] = OP_MUL,
	[ TK_MULEQ ] = OP_MULEQ,
	[ TK_POW ] = OP_POW,
	[ TK_POWEQ ] = OP_POWEQ,
	[ TK_DIV ] = OP_DIV,
	[ TK_DIVEQ ] = OP_DIVEQ,
	[ TK_MOD ] = OP_MOD,
	[ TK_MODEQ ] = OP_MODEQ,
	[ TK_BAND ] = OP_BAND,
	[ TK_BANDEQ ] = OP_BANDEQ,
	[ TK_AND ] = OP_AND,
	[ TK_BOR ] = OP_BOR,
	[ TK_BOREQ ] = OP_BOREQ,
	[ TK_OR ] = OP_OR,
	[ TK_BXOR ] = OP_BXOR,
	[ TK_BXOREQ ] = OP_BXOREQ,
	[ TK_EQ ] = OP_NOP, /* Not the assignment operator */
	[ TK_EQEQ ] = OP_EQ,
	[ TK_LT ] = OP_LT,
	[ TK_LE ] = OP_LE,
	[ TK_LSH ] = OP_LSH,
	[ TK_LSHEQ ] = OP_LSHEQ,
	[ TK_GT ] = OP_GT,
	[ TK_GE ] = OP_GE,
	[ TK_RSH ] = OP_RSH,
	[ TK_RSHEQ ] = OP_RSHEQ,
	[ TK_COLON ] = OP_MOV,
	// [ TK_RET ] = OP_RET
};