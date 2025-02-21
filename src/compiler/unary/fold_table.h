static Label *ops[ ] =
{	/* unary ops only */
	[ 0 ... OP_N - 1 ] = &&ERR,
	[ OP_NOT ] = &&NOT,
	[ OP_BNOT ] = &&BNOT,
	[ OP_ADD ] = &&PLUS,
	[ OP_SUB ] = &&MINUS,
	[ OP_PREINC ] = &&INC,
	[ OP_PREDEC ] = &&DEC,
};