stil opcode binary_op_to_compound( ir* op, ir* l, ir* r )
{	/* COMPOUND = OPCODE + LEFT * NVALUES + RIGHT */
	return op->value.i64 + ( l->value.type * value_n + r->value.type );
}

stil u32 binary_ir_to_idx( ir* l, ir* r )
{
	return l->type * value_n + r->type;
}

void binary_compile( compiler* c, parser* p )
{
	static void* irs[ ] = { IRS( , X_BINIR_LBL1 ) };
	ir* rhs = vec_pop( p->irs );
	ir* op = vec_pop( p->irs );
	ir* lhs = vec_pop( p->irs );
	opcode oc = binary_op_to_compound( op, lhs, rhs );
	goto *irs[ binary_ir_to_idx( lhs, rhs ) ];
	IRS( , X_BINIR_FN1 )
}