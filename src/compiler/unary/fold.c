void unary_fold( compiler* c, opcode oc, ir* rhs )
{
	// static const void* ops[ ] = { UNOPS( , X_OPCODE_LBL1 ) UNARIES2( , X_OPCODE_LBL1 ) };
	// value* rv = &r->value;
	// goto *ops[ opcode ];

	// not_i64: UNA_EVAL( i64, !rv->i64 );
	// not_f64: UNA_EVAL( i64, !rv->f64 );
	// not_str: UNA_EVAL( i64, !rv->str );

	// bnot_i64: UNA_EVAL( i64, ~rv->i64 );
	// bnot_f64: UNA_EVAL( i64, ~( i64 )rv->f64 );
	// bnot_str: UNA_EVAL( i64, ~rv->str->len );

	// len_i64: UNA_EVAL( i64, rv->i64 );
	// len_f64: UNA_EVAL( i64, ( i64 )rv->f64 ); /* count mantissa digits? */
	// len_str: UNA_EVAL( i64, rv->str->len );

	// ret_i64: UNA_EVAL( i64, rv->i64 );
	// ret_f64: UNA_EVAL( f64, rv->f64 );
	// ret_str: UNA_EVAL( str, rv->str );

	// add_i64: UNA_EVAL( i64, +rv->i64 );
	// add_f64: UNA_EVAL( f64, +rv->f64 );
	// add_str: UNA_EVAL( i64, +rv->str->len );

	// sub_i64: UNA_EVAL( i64, -rv->i64 );
	// sub_f64: UNA_EVAL( f64, -rv->f64 );
	// sub_str: UNA_EVAL( i64, -rv->str->len );
}