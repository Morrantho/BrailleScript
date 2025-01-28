void binary_fold( ir* out, ir* l, opcode oc, ir* r )
{
	// static const void* ops[ ] = { BINOPS( , X_BINARY_LBL ) };
	// oc -= op_add_i64;
	// value* lv = &l->value;
	// value* rv = &r->value;
	// goto *ops[ oc ];

	// add_i64: BIN_EVAL( i64, lv->i64 + rv->i64 );
	// add_f64: BIN_EVAL( f64, lv->f64 + rv->f64 );
	// add_str: BIN_EVAL( i64, lv->str->len + rv->str->len );

	// sub_i64: BIN_EVAL( i64, lv->i64 - rv->i64 );
	// sub_f64: BIN_EVAL( f64, lv->f64 - rv->f64 );
	// sub_str: BIN_EVAL( i64, lv->str->len - rv->str->len );

	// mul_i64: BIN_EVAL( i64, lv->i64 * rv->i64 );
	// mul_f64: BIN_EVAL( f64, lv->f64 * rv->f64 );
	// mul_str: BIN_EVAL( i64, lv->str->len * rv->str->len );

	// div_i64: BIN_EVAL( i64, lv->i64 / rv->i64 );
	// div_f64: BIN_EVAL( f64, lv->f64 / rv->f64 );
	// div_str: BIN_EVAL( i64, lv->str->len / rv->str->len );

	// mod_i64: BIN_EVAL( i64, lv->i64 % rv->i64 );
	// mod_f64: BIN_EVAL( i64, ( i64 )lv->f64 % ( i64 )rv->f64 );
	// mod_str: BIN_EVAL( i64, lv->str->len % rv->str->len );

	// pow_i64: BIN_EVAL( f64, pow( ( f64 )lv->i64, ( f64 )rv->i64 ) );
	// pow_f64: BIN_EVAL( f64, pow( lv->f64, rv->f64 ) );
	// pow_str: BIN_EVAL( f64, pow( ( f64 )lv->str->len, ( f64 )rv->str->len ) );

	// band_i64: BIN_EVAL( i64, lv->i64 & rv->i64 );
	// band_f64: BIN_EVAL( i64, ( i64 )lv->f64 & ( i64 )rv->f64 );
	// band_str: BIN_EVAL( i64, lv->str->len & rv->str->len );

	// bor_i64: BIN_EVAL( i64, lv->i64 | rv->i64 );
	// bor_f64: BIN_EVAL( i64, ( i64 )lv->f64 | ( i64 )rv->f64 );
	// bor_str: BIN_EVAL( i64, lv->str->len | rv->str->len );

	// bxor_i64: BIN_EVAL( i64, lv->i64 ^ rv->i64 );
	// bxor_f64: BIN_EVAL( i64, ( i64 )lv->f64 ^ ( i64 )rv->f64 );
	// bxor_str: BIN_EVAL( i64, lv->str->len ^ rv->str->len );

	// lsh_i64: BIN_EVAL( i64, lv->i64 << rv->i64 );
	// lsh_f64: BIN_EVAL( i64, ( i64 )lv->f64 << ( i64 )rv->f64 );
	// lsh_str: BIN_EVAL( i64, lv->str->len << rv->str->len );

	// rsh_i64: BIN_EVAL( i64, lv->i64 >> rv->i64 );
	// rsh_f64: BIN_EVAL( i64, ( i64 )lv->f64 >> ( i64 )rv->f64 );
	// rsh_str: BIN_EVAL( i64, lv->str->len >> rv->str->len );

	// eqeq_i64: BIN_EVAL( i64, lv->i64 == rv->i64 );
	// eqeq_f64: BIN_EVAL( i64, lv->f64 == rv->f64 );
	// eqeq_str: BIN_EVAL( i64, lv->str == rv->str );

	// neq_i64: BIN_EVAL( i64, lv->i64 != rv->i64 );
	// neq_f64: BIN_EVAL( i64, lv->f64 != rv->f64 );
	// neq_str: BIN_EVAL( i64, lv->str != rv->str );

	// lt_i64: BIN_EVAL( i64, lv->i64 < rv->i64 );
	// lt_f64: BIN_EVAL( i64, lv->f64 < rv->f64 );
	// lt_str: BIN_EVAL( i64, lv->str < rv->str );

	// le_i64: BIN_EVAL( i64, lv->i64 <= rv->i64 );
	// le_f64: BIN_EVAL( i64, lv->f64 <= rv->f64 );
	// le_str: BIN_EVAL( i64, lv->str <= rv->str );

	// gt_i64: BIN_EVAL( i64, lv->i64 > rv->i64 );
	// gt_f64: BIN_EVAL( i64, lv->f64 > rv->f64 );
	// gt_str: BIN_EVAL( i64, lv->str > rv->str );

	// ge_i64: BIN_EVAL( i64, lv->i64 >= rv->i64 );
	// ge_f64: BIN_EVAL( i64, lv->f64 >= rv->f64 );
	// ge_str: BIN_EVAL( i64, lv->str >= rv->str );

	// and_i64: BIN_EVAL( i64, lv->i64 && rv->i64 );
	// and_f64: BIN_EVAL( i64, lv->f64 && rv->f64 );
	// and_str: BIN_EVAL( i64, lv->str && rv->str );

	// or_i64: BIN_EVAL( i64, lv->i64 || rv->i64 );
	// or_f64: BIN_EVAL( i64, lv->f64 || rv->f64 );
	// or_str: BIN_EVAL( i64, lv->str || rv->str );

	// addeq_i64: BIN_EVAL( i64, lv->i64 + rv->i64 );
	// addeq_f64: BIN_EVAL( f64, lv->f64 + rv->f64 );
	// addeq_str: BIN_EVAL( i64, lv->str->len + rv->str->len );

	// subeq_i64: BIN_EVAL( i64, lv->i64 - rv->i64 );
	// subeq_f64: BIN_EVAL( f64, lv->f64 - rv->f64 );
	// subeq_str: BIN_EVAL( i64, lv->str->len - rv->str->len );

	// muleq_i64: BIN_EVAL( i64, lv->i64 * rv->i64 );
	// muleq_f64: BIN_EVAL( f64, lv->f64 * rv->f64 );
	// muleq_str: BIN_EVAL( i64, lv->str->len * rv->str->len );

	// diveq_i64: BIN_EVAL( i64, lv->i64 / rv->i64 );
	// diveq_f64: BIN_EVAL( f64, lv->f64 / rv->f64 );
	// diveq_str: BIN_EVAL( i64, lv->str->len / rv->str->len );

	// modeq_i64: BIN_EVAL( i64, lv->i64 % rv->i64 );
	// modeq_f64: BIN_EVAL( i64, ( i64 )lv->f64 % ( i64 )rv->f64 );
	// modeq_str: BIN_EVAL( i64, lv->str->len % rv->str->len );

	// bandeq_i64: BIN_EVAL( i64, lv->i64 & rv->i64 );
	// bandeq_f64: BIN_EVAL( i64, ( i64 )lv->f64 & ( i64 )rv->f64 );
	// bandeq_str: BIN_EVAL( i64, lv->str->len & rv->str->len );

	// boreq_i64: BIN_EVAL( i64, lv->i64 | rv->i64 );
	// boreq_f64: BIN_EVAL( i64, ( i64 )lv->f64 | ( i64 )rv->f64 );
	// boreq_str: BIN_EVAL( i64, lv->str->len | rv->str->len );

	// bxoreq_i64: BIN_EVAL( i64, lv->i64 ^ rv->i64 );
	// bxoreq_f64: BIN_EVAL( i64, ( i64 )lv->f64 ^ ( i64 )rv->f64 );
	// bxoreq_str: BIN_EVAL( i64, lv->str->len ^ rv->str->len );

	// lsheq_i64: BIN_EVAL( i64, lv->i64 << rv->i64 );
	// lsheq_f64: BIN_EVAL( i64, ( i64 )lv->f64 << ( i64 )rv->f64 );
	// lsheq_str: BIN_EVAL( i64, lv->str->len << rv->str->len );

	// rsheq_i64: BIN_EVAL( i64, lv->i64 >> rv->i64 );
	// rsheq_f64: BIN_EVAL( i64, ( i64 )lv->f64 >> ( i64 )rv->f64 );
	// rsheq_str: BIN_EVAL( i64, lv->str->len >> rv->str->len );
}