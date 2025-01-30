void binary_fold( compiler* c, ir* l, opcode oc, ir* r )
{
	static const void* ops[ ] = { BINOPS( &&op_, X_OP_VALUE ) };
	ir* out = vec_commit( c->parser->irs );
	out->type = ir_const;
	// oc -= op_add_i64;
	value* lv = &l->value;
	value* rv = &r->value;
	goto *ops[ oc ];

	op_add_i64: EVAL( i64, lv->i64 + rv->i64 )
	op_add_f64: EVAL( f64, lv->f64 + rv->f64 )
	op_add_str: EVAL( i64, lv->str->len + rv->str->len )

	op_sub_i64: EVAL( i64, lv->i64 - rv->i64 )
	op_sub_f64: EVAL( f64, lv->f64 - rv->f64 )
	op_sub_str: EVAL( i64, lv->str->len - rv->str->len )

	op_mul_i64: EVAL( i64, lv->i64 * rv->i64 )
	op_mul_f64: EVAL( f64, lv->f64 * rv->f64 )
	op_mul_str: EVAL( i64, lv->str->len * rv->str->len )

	op_div_i64: EVAL( i64, lv->i64 / rv->i64 )
	op_div_f64: EVAL( f64, lv->f64 / rv->f64 )
	op_div_str: EVAL( i64, lv->str->len / rv->str->len )

	op_mod_i64: EVAL( i64, lv->i64 % rv->i64 )
	op_mod_f64: EVAL( f64, ( i64 )lv->f64 % ( i64 )rv->f64 )
	op_mod_str: EVAL( i64, lv->str->len % rv->str->len )

	op_pow_i64: EVAL( i64, ( i64 )pow( ( f64 )lv->i64, ( f64 )rv->i64 ) )
	op_pow_f64: EVAL( f64,  pow( lv->i64, rv->i64 ) )
	op_pow_str: EVAL( i64, ( i64 )pow( ( f64 )lv->str->len, ( f64 )rv->str->len ) )

	op_band_i64: EVAL( i64, lv->i64 & rv->i64 )
	op_band_f64: EVAL( f64, ( i64 )lv->f64 & ( i64 )rv->f64 )
	op_band_str: EVAL( i64, lv->str->len & rv->str->len )

	op_bor_i64: EVAL( i64, lv->i64 | rv->i64 )
	op_bor_f64: EVAL( f64, ( i64 )lv->f64 | ( i64 )rv->f64 )
	op_bor_str: EVAL( i64, lv->str->len | rv->str->len )

	op_bxor_i64: EVAL( i64, lv->i64 ^ rv->i64 )
	op_bxor_f64: EVAL( f64, ( i64 )lv->f64 ^ ( i64 )rv->f64 )
	op_bxor_str: EVAL( i64, lv->str->len ^ rv->str->len )

	op_lsh_i64: EVAL( i64, lv->i64 << rv->i64 )
	op_lsh_f64: EVAL( f64, ( i64 )lv->f64 << ( i64 )rv->f64 )
	op_lsh_str: EVAL( i64, lv->str->len << rv->str->len )

	op_rsh_i64: EVAL( i64, lv->i64 >> rv->i64 )
	op_rsh_f64: EVAL( f64, ( i64 )lv->f64 >> ( i64 )rv->f64 )
	op_rsh_str: EVAL( i64, lv->str->len >> rv->str->len )

	op_eqeq_i64: EVAL( i64, lv->i64 == rv->i64 )
	op_eqeq_f64: EVAL( f64, lv->f64 == rv->f64 )
	op_eqeq_str: EVAL( i64, lv->str == rv->str )

	op_neq_i64: EVAL( i64, lv->i64 != rv->i64 )
	op_neq_f64: EVAL( f64, lv->f64 != rv->f64 )
	op_neq_str: EVAL( i64, lv->str != rv->str )

	op_lt_i64: EVAL( i64, lv->i64 < rv->i64 )
	op_lt_f64: EVAL( f64, lv->f64 < rv->f64 )
	op_lt_str: EVAL( i64, lv->str < rv->str )

	op_le_i64: EVAL( i64, lv->i64 <= rv->i64 )
	op_le_f64: EVAL( f64, lv->f64 <= rv->f64 )
	op_le_str: EVAL( i64, lv->str <= rv->str )

	op_gt_i64: EVAL( i64, lv->i64 > rv->i64 )
	op_gt_f64: EVAL( f64, lv->f64 > rv->f64 )
	op_gt_str: EVAL( i64, lv->str > rv->str )

	op_ge_i64: EVAL( i64, lv->i64 >= rv->i64 )
	op_ge_f64: EVAL( f64, lv->f64 >= rv->f64 )
	op_ge_str: EVAL( i64, lv->str >= rv->str )

	op_and_i64: EVAL( i64, lv->i64 && rv->i64 )
	op_and_f64: EVAL( f64, lv->f64 && rv->f64 )
	op_and_str: EVAL( i64, lv->str && rv->str )

	op_or_i64: EVAL( i64, lv->i64 || rv->i64 )
	op_or_f64: EVAL( f64, lv->f64 || rv->f64 )
	op_or_str: EVAL( i64, lv->str || rv->str )

	op_addeq_i64: EVAL( i64, lv->i64 + rv->i64 )
	op_addeq_f64: EVAL( f64, lv->f64 + rv->f64 )
	op_addeq_str: EVAL( i64, lv->str->len + rv->str->len )

	op_subeq_i64: EVAL( i64, lv->i64 - rv->i64 )
	op_subeq_f64: EVAL( f64, lv->f64 - rv->f64 )
	op_subeq_str: EVAL( i64, lv->str->len - rv->str->len )

	op_muleq_i64: EVAL( i64, lv->i64 * rv->i64 )
	op_muleq_f64: EVAL( f64, lv->f64 * rv->f64 )
	op_muleq_str: EVAL( i64, lv->str->len * rv->str->len )

	op_diveq_i64: EVAL( i64, lv->i64 / rv->i64 )
	op_diveq_f64: EVAL( f64, lv->f64 / rv->f64 )
	op_diveq_str: EVAL( i64, lv->str->len / rv->str->len )

	op_modeq_i64: EVAL( i64, lv->i64 % rv->i64 )
	op_modeq_f64: EVAL( f64, ( i64 )lv->f64 % ( i64 )rv->f64 )
	op_modeq_str: EVAL( i64, lv->str->len % rv->str->len )

	op_bandeq_i64: EVAL( i64, lv->i64 & rv->i64 )
	op_bandeq_f64: EVAL( f64, ( i64 )lv->f64 & ( i64 )rv->f64 )
	op_bandeq_str: EVAL( i64, lv->str->len & rv->str->len )	

	op_boreq_i64: EVAL( i64, lv->i64 | rv->i64 )
	op_boreq_f64: EVAL( f64, ( i64 )lv->f64 | ( i64 )rv->f64 )
	op_boreq_str: EVAL( i64, lv->str->len | rv->str->len )	

	op_bxoreq_i64: EVAL( i64, lv->i64 ^ rv->i64 )
	op_bxoreq_f64: EVAL( f64, ( i64 )lv->f64 ^ ( i64 )rv->f64 )
	op_bxoreq_str: EVAL( i64, lv->str->len ^ rv->str->len )	

	op_lsheq_i64: EVAL( i64, lv->i64 << rv->i64 )
	op_lsheq_f64: EVAL( f64, ( i64 )lv->f64 << ( i64 )rv->f64 )
	op_lsheq_str: EVAL( i64, lv->str->len << rv->str->len )	

	op_rsheq_i64: EVAL( i64, lv->i64 >> rv->i64 )
	op_rsheq_f64: EVAL( f64, ( i64 )lv->f64 >> ( i64 )rv->f64 )
	op_rsheq_str: EVAL( i64, lv->str->len >> rv->str->len )	
}