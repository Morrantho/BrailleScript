/* Promote both irs to a common type */
stil value_type bin_promote( ir* l, ir* r )
{
	static value_type types[ value_n * value_n ] =
	{ /* i64		f64		   str  	*/
/* i64 */value_i64, value_f64, value_str,
/* f64 */value_f64, value_f64, value_str,
/* str */value_str, value_str, value_str
	};
	return types[ l->value.type * value_n + r->value.type ];
}

/* Convert base binary opcode to compound binary opcode from common type. */
stil opcode bin_compound( ir* op, value_type common )
{
	return op->value.i64 + common;
}

/* Convert left and right ir's to 1d index, offset by the first */
/* compilable ir_type */
stil u32 bin_ir_idx( ir* l, ir* r )
{
	u32 ltype = l->type - IR_CMP_BASE;
	u32 rtype = r->type - IR_CMP_BASE;
	return ltype * IR_CMP_N + rtype;
}

void binary_compile( compiler* c, parser* p )
{
	static void* irs[ ] = { CMP_IRS( , X_BINIR_LBL1 ) };
	ir* rhs = vec_pop( p->irs );
	ir* op = vec_pop( p->irs );
	ir* lhs = vec_pop( p->irs );
	value_type common = bin_promote( lhs, rhs );
	bin_cast( lhs, common );
	bin_cast( rhs, common );
	opcode oc = bin_compound( op, common );
	goto *irs[ bin_ir_idx( lhs, rhs ) ];
	CMP_IRS( , X_BINIR_FN1 )
}