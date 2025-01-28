stil opcode unary_op_to_compound( ir* op, ir* r )
{	/* COMPOUND = OPCODE + RTYPE */
	return op->value.i64 + r->value.type;
}

void unary_compile( compiler* c, parser* p )
{
	static const void* irs[ ] = { IRS( , X_UNAIR_LBL1 ) };
	ir* rhs = vec_pop( p->irs );
	ir* op = vec_pop( p->irs ); /* op->value.i64 = opcode */
	opcode oc = unary_op_to_compound( op, rhs );
	goto *irs[ rhs->type ];
	IRS( , X_UNAIR_FN1 )
}