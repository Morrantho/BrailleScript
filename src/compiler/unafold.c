u8 una_foldable( ir* op )
{
	return op->ir_type == ir_const;
}

void una_fold( ir* out, ir* op, ir* r )
{
	static const void* ops[ ][ value_n ] =
	{
		OP_UNA( , X_UNA_LBL )
		OP_UNA2( , X_UNA_LBL )
	};
	out->ir_type = ir_const;
	opcode opcode = op->i64;
	goto *ops[ opcode ][ r->value_type ];

	not_i64: UNA_EVAL( i64, !r->i64 );
	not_f64: UNA_EVAL( i64, !r->f64 );
	not_str: UNA_EVAL( i64, !r->str );

	bnot_i64: UNA_EVAL( i64, ~r->i64 );
	bnot_f64: UNA_EVAL( i64, ~( i64 )r->f64 );
	bnot_str: UNA_EVAL( i64, ~r->str->len );

	len_i64: UNA_EVAL( i64, r->i64 );
	len_f64: UNA_EVAL( i64, ( i64 )r->f64 ); /* count mantissa digits? */
	len_str: UNA_EVAL( i64, r->str->len );

	ret_i64: UNA_EVAL( i64, r->i64 );
	ret_f64: UNA_EVAL( f64, r->f64 );
	ret_str: UNA_EVAL( str, r->str );

	plus_i64: UNA_EVAL( i64, +r->i64 );
	plus_f64: UNA_EVAL( f64, +r->f64 );
	plus_str: UNA_EVAL( i64, +r->str->len );

	neg_i64: UNA_EVAL( i64, -r->i64 );
	neg_f64: UNA_EVAL( f64, -r->f64 );
	neg_str: UNA_EVAL( i64, -r->str->len );
}
