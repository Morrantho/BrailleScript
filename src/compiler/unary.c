u8 unary_foldable( ir* op )
{
	return op->ir_type == ir_const;
}

void unary_fold( ir* out, opcode opcode, ir* r )
{
	static const void* ops[ ][ value_n ] = { OP_UNA( , X_UNA_LBL ) OP_UNA2( , X_UNA_LBL ) };
	out->ir_type = ir_const;
	value* rv = &r->value;
	goto *ops[ opcode ][ rv->type ];

	not_i64: UNA_EVAL( i64, !rv->i64 );
	not_f64: UNA_EVAL( i64, !rv->f64 );
	not_str: UNA_EVAL( i64, !rv->str );

	bnot_i64: UNA_EVAL( i64, ~rv->i64 );
	bnot_f64: UNA_EVAL( i64, ~( i64 )rv->f64 );
	bnot_str: UNA_EVAL( i64, ~rv->str->len );

	len_i64: UNA_EVAL( i64, rv->i64 );
	len_f64: UNA_EVAL( i64, ( i64 )rv->f64 ); /* count mantissa digits? */
	len_str: UNA_EVAL( i64, rv->str->len );

	ret_i64: UNA_EVAL( i64, rv->i64 );
	ret_f64: UNA_EVAL( f64, rv->f64 );
	ret_str: UNA_EVAL( str, rv->str );

	plus_i64: UNA_EVAL( i64, +rv->i64 );
	plus_f64: UNA_EVAL( f64, +rv->f64 );
	plus_str: UNA_EVAL( i64, +rv->str->len );

	neg_i64: UNA_EVAL( i64, -rv->i64 );
	neg_f64: UNA_EVAL( f64, -rv->f64 );
	neg_str: UNA_EVAL( i64, -rv->str->len );
}

void unary_compile( compiler* compiler, parser* parser )
{
	static const void* irs[ ] = { IRS( ir_, X_IRS_LBL ) };
	ir* rhs = vec_pop( parser->irs );
	ir* op_ir = vec_pop( parser->irs );
	opcode oc = op_ir->value.i64;
	ir* out = vec_commit( parser->irs );
	goto *irs[ rhs->ir_type ];
	ERR:
	CONST:
		unary_fold( out, oc, rhs );
		out->idx = const_push( compiler, &out->value );
		return;
	REF:
		var* var = var_get( compiler, out->value.str );
		/* TODO: if( !var ) throw( BAD_REF ) */
		out->idx = var->idx;
		// op ins = { .op = op_ir->value.i64 };
		// ins.r = var->idx;
		// ins.a = var->idx;
		// op_push( compiler, &ins );
		return;
	CALL:
		return;
}