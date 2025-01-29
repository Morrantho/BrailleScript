/* Convert base binary opcode to compound binary opcode */
stil opcode bin2op( ir* op, ir* l, ir* r )
{	/* COMPOUND = OPCODE + LEFT * NVALUES + RIGHT */
	return op->value.i64 + ( l->value.type * value_n + r->value.type );
}

/* Convert left and right ir's to 1d index, offset by the first */
/* compilable ir_type */
stil u32 bin2idx( ir* l, ir* r )
{
	return ( l->type - IR_CMP_BASE ) * IR_CMP_N + ( r->type - IR_CMP_BASE );
}

void binary_compile( compiler* c, parser* p )
{
	static void* irs[ ] = { CMP_IRS( , X_BINIR_LBL1 ) };
	ir* rhs = vec_pop( p->irs );
	ir* op = vec_pop( p->irs );
	ir* lhs = vec_pop( p->irs );
	opcode oc = bin2op( op, lhs, rhs );
	goto *irs[ bin2idx( lhs, rhs ) ];
	CMP_IRS( , X_BINIR_FN1 )
}