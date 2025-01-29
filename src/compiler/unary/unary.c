/* Converts base unary opcode to compound unary opcode */
stil opcode una_compound( ir* op, ir* r )
{	/* COMPOUND = OPCODE + RTYPE */
	return op->value.i64 + r->value.type;
}

/* Converts ir to 1d index, offset by the first compilable ir_type. */
stil u32 una_ir_idx( ir* r )
{
	return r->type - IR_CMP_BASE;
}

void unary_compile( compiler* c, parser* p )
{
	static const void* irs[ ] = { CMP_IRS( , X_UNAIR_LBL1 ) };
	ir* rhs = vec_pop( p->irs );
	ir* op = vec_pop( p->irs ); /* op->value.i64 = opcode */
	opcode oc = una_compound( op, rhs );
	goto *irs[ una_ir_idx( rhs ) ];
	CMP_IRS( , X_UNAIR_FN1 )
}