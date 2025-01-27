u8 binary_foldable( ir* lhs, ir* rhs )
{
	return lhs->ir_type == ir_const && rhs->ir_type == ir_const;
}

void binary_fold( ir* out, ir* l, opcode oc, ir* r )
{
	static const void* ops[ ][ value_n ][ value_n ] = { OP_BIN( , X_BIN_LBL ) };
	out->ir_type = ir_const;
	oc -= op_add;
	value* lv = &l->value;
	value* rv = &r->value;
	goto *ops[ oc ][ lv->type ][ rv->type ];

	add_i64_i64: BIN_EVAL( i64, lv->i64 + rv->i64 );
	add_i64_f64: BIN_EVAL( f64, ( f64 )lv->i64 + rv->f64 );
	add_i64_str: BIN_EVAL( i64, lv->i64 + rv->str->len );
	add_f64_i64: BIN_EVAL( f64, lv->f64 + ( f64 )rv->i64 );
	add_f64_f64: BIN_EVAL( f64, lv->f64 + rv->f64 );
	add_f64_str: BIN_EVAL( f64, lv->f64 + ( f64 )rv->str->len );
	add_str_i64: BIN_EVAL( i64, lv->str->len + rv->i64 );
	add_str_f64: BIN_EVAL( f64, ( f64 )lv->str->len + rv->f64 );
	add_str_str: BIN_EVAL( i64, lv->str->len + rv->str->len );

	sub_i64_i64: BIN_EVAL( i64, lv->i64 - rv->i64 );
	sub_i64_f64: BIN_EVAL( f64, ( f64 )lv->i64 - rv->f64 );
	sub_i64_str: BIN_EVAL( i64, lv->i64 - rv->str->len );
	sub_f64_i64: BIN_EVAL( f64, lv->f64 - ( f64 )rv->i64 );
	sub_f64_f64: BIN_EVAL( f64, lv->f64 - rv->f64 );
	sub_f64_str: BIN_EVAL( f64, lv->f64 - ( f64 )rv->str->len );
	sub_str_i64: BIN_EVAL( i64, lv->str->len - rv->i64 );
	sub_str_f64: BIN_EVAL( f64, ( f64 )lv->str->len - rv->f64 );
	sub_str_str: BIN_EVAL( i64, lv->str->len - rv->str->len );

	mul_i64_i64: BIN_EVAL( i64, lv->i64 * rv->i64 );
	mul_i64_f64: BIN_EVAL( f64, ( f64 )lv->i64 * rv->f64 );
	mul_i64_str: BIN_EVAL( i64, lv->i64 * rv->str->len );
	mul_f64_i64: BIN_EVAL( f64, lv->f64 * ( f64 )rv->i64 );
	mul_f64_f64: BIN_EVAL( f64, lv->f64 * rv->f64 );
	mul_f64_str: BIN_EVAL( f64, lv->f64 * ( f64 )rv->str->len );
	mul_str_i64: BIN_EVAL( i64, lv->str->len * rv->i64 );
	mul_str_f64: BIN_EVAL( f64, ( f64 )lv->str->len * rv->f64 );
	mul_str_str: BIN_EVAL( i64, lv->str->len * rv->str->len );

	div_i64_i64: BIN_EVAL( i64, lv->i64 / rv->i64 );
	div_i64_f64: BIN_EVAL( f64, ( f64 )lv->i64 / rv->f64 );
	div_i64_str: BIN_EVAL( i64, lv->i64 / rv->str->len );
	div_f64_i64: BIN_EVAL( f64, lv->f64 / ( f64 )rv->i64 );
	div_f64_f64: BIN_EVAL( f64, lv->f64 / rv->f64 );
	div_f64_str: BIN_EVAL( f64, lv->f64 / ( f64 )rv->str->len );
	div_str_i64: BIN_EVAL( i64, lv->str->len / rv->i64 );
	div_str_f64: BIN_EVAL( f64, ( f64 )lv->str->len / rv->f64 );
	div_str_str: BIN_EVAL( i64, lv->str->len / rv->str->len );

	mod_i64_i64: BIN_EVAL( i64, lv->i64 % rv->i64 );
	mod_i64_f64: BIN_EVAL( i64, lv->i64 % ( i64 )rv->f64 );
	mod_i64_str: BIN_EVAL( i64, lv->i64 % rv->str->len );
	mod_f64_i64: BIN_EVAL( i64, ( i64 )lv->f64 % rv->i64 );
	mod_f64_f64: BIN_EVAL( i64, ( i64 )lv->f64 % ( i64 )rv->f64 );
	mod_f64_str: BIN_EVAL( i64, ( i64 )lv->f64 % rv->str->len );
	mod_str_i64: BIN_EVAL( i64, lv->str->len % rv->i64 );
	mod_str_f64: BIN_EVAL( i64, lv->str->len % ( i64 )rv->f64 );
	mod_str_str: BIN_EVAL( i64, lv->str->len % rv->str->len );

	pow_i64_i64: BIN_EVAL( f64, pow( ( f64 )lv->i64, ( f64 )rv->i64 ) );
	pow_i64_f64: BIN_EVAL( f64, pow( ( f64 )lv->i64, rv->f64 ) );
	pow_i64_str: BIN_EVAL( f64, pow( ( f64 )lv->i64, ( f64 )rv->str->len ) );
	pow_f64_i64: BIN_EVAL( f64, pow( lv->f64, ( f64 )rv->i64 ) );
	pow_f64_f64: BIN_EVAL( f64, pow( lv->f64, rv->f64 ) );
	pow_f64_str: BIN_EVAL( f64, pow( lv->f64, ( f64 )rv->str->len ) );
	pow_str_i64: BIN_EVAL( f64, pow( ( f64 )lv->str->len, ( f64 )rv->i64 ) );
	pow_str_f64: BIN_EVAL( f64, pow( ( f64 )lv->str->len, rv->f64 ) );
	pow_str_str: BIN_EVAL( f64, pow( ( f64 )lv->str->len, ( f64 )rv->str->len ) );

	band_i64_i64: BIN_EVAL( i64, lv->i64 & rv->i64 );
	band_i64_f64: BIN_EVAL( i64, lv->i64 & ( i64 )rv->f64 );
	band_i64_str: BIN_EVAL( i64, lv->i64 & rv->str->len );
	band_f64_i64: BIN_EVAL( i64, ( i64 )lv->f64 & rv->i64 );
	band_f64_f64: BIN_EVAL( i64, ( i64 )lv->f64 & ( i64 )rv->f64 );
	band_f64_str: BIN_EVAL( i64, ( i64 )lv->f64 & rv->str->len );
	band_str_i64: BIN_EVAL( i64, lv->str->len & rv->i64 );
	band_str_f64: BIN_EVAL( i64, lv->str->len & ( i64 )rv->f64 );
	band_str_str: BIN_EVAL( i64, lv->str->len & rv->str->len );

	bor_i64_i64: BIN_EVAL( i64, lv->i64 | rv->i64 );
	bor_i64_f64: BIN_EVAL( i64, lv->i64 | ( i64 )rv->f64 );
	bor_i64_str: BIN_EVAL( i64, lv->i64 | rv->str->len );
	bor_f64_i64: BIN_EVAL( i64, ( i64 )lv->f64 | rv->i64 );
	bor_f64_f64: BIN_EVAL( i64, ( i64 )lv->f64 | ( i64 )rv->f64 );
	bor_f64_str: BIN_EVAL( i64, ( i64 )lv->f64 | rv->str->len );
	bor_str_i64: BIN_EVAL( i64, lv->str->len | rv->i64 );
	bor_str_f64: BIN_EVAL( i64, lv->str->len | ( i64 )rv->f64 );
	bor_str_str: BIN_EVAL( i64, lv->str->len | rv->str->len );

	bxor_i64_i64: BIN_EVAL( i64, lv->i64 ^ rv->i64 );
	bxor_i64_f64: BIN_EVAL( i64, lv->i64 ^ ( i64 )rv->f64 );
	bxor_i64_str: BIN_EVAL( i64, lv->i64 ^ rv->str->len );
	bxor_f64_i64: BIN_EVAL( i64, ( i64 )lv->f64 ^ rv->i64 );
	bxor_f64_f64: BIN_EVAL( i64, ( i64 )lv->f64 ^ ( i64 )rv->f64 );
	bxor_f64_str: BIN_EVAL( i64, ( i64 )lv->f64 ^ rv->str->len );
	bxor_str_i64: BIN_EVAL( i64, lv->str->len ^ rv->i64 );
	bxor_str_f64: BIN_EVAL( i64, lv->str->len ^ ( i64 )rv->f64 );
	bxor_str_str: BIN_EVAL( i64, lv->str->len ^ rv->str->len );

	lsh_i64_i64: BIN_EVAL( i64, lv->i64 << rv->i64 );
	lsh_i64_f64: BIN_EVAL( i64, lv->i64 << ( i64 )rv->f64 );
	lsh_i64_str: BIN_EVAL( i64, lv->i64 << rv->str->len );
	lsh_f64_i64: BIN_EVAL( i64, ( i64 )lv->f64 << rv->i64 );
	lsh_f64_f64: BIN_EVAL( i64, ( i64 )lv->f64 << ( i64 )rv->f64 );
	lsh_f64_str: BIN_EVAL( i64, ( i64 )lv->f64 << rv->str->len );
	lsh_str_i64: BIN_EVAL( i64, lv->str->len << rv->i64 );
	lsh_str_f64: BIN_EVAL( i64, lv->str->len << ( i64 )rv->f64 );
	lsh_str_str: BIN_EVAL( i64, lv->str->len << rv->str->len );

	rsh_i64_i64: BIN_EVAL( i64, lv->i64 >> rv->i64 );
	rsh_i64_f64: BIN_EVAL( i64, lv->i64 >> ( i64 )rv->f64 );
	rsh_i64_str: BIN_EVAL( i64, lv->i64 >> rv->str->len );
	rsh_f64_i64: BIN_EVAL( i64, ( i64 )lv->f64 >> rv->i64 );
	rsh_f64_f64: BIN_EVAL( i64, ( i64 )lv->f64 >> ( i64 )rv->f64 );
	rsh_f64_str: BIN_EVAL( i64, ( i64 )lv->f64 >> rv->str->len );
	rsh_str_i64: BIN_EVAL( i64, lv->str->len >> rv->i64 );
	rsh_str_f64: BIN_EVAL( i64, lv->str->len >> ( i64 )rv->f64 );
	rsh_str_str: BIN_EVAL( i64, lv->str->len >> rv->str->len );

	eqeq_i64_i64: BIN_EVAL( i64, lv->i64 == rv->i64 );
	eqeq_i64_f64: BIN_EVAL( i64, ( f64 )lv->i64 == rv->f64 );
	eqeq_i64_str: BIN_EVAL( i64, lv->i64 == rv->str->len );
	eqeq_f64_i64: BIN_EVAL( i64, lv->f64 == ( f64 )rv->i64 );
	eqeq_f64_f64: BIN_EVAL( i64, lv->f64 == rv->f64 );
	eqeq_f64_str: BIN_EVAL( i64, lv->f64 == ( f64 )rv->str->len );
	eqeq_str_i64: BIN_EVAL( i64, lv->str->len == rv->i64 );
	eqeq_str_f64: BIN_EVAL( i64, ( f64 )lv->str->len == rv->f64 );
	eqeq_str_str: BIN_EVAL( i64, lv->str == rv->str );

	neq_i64_i64: BIN_EVAL( i64, lv->i64 != rv->i64 );
	neq_i64_f64: BIN_EVAL( i64, ( f64 )lv->i64 != rv->f64 );
	neq_i64_str: BIN_EVAL( i64, lv->i64 != rv->str->len );
	neq_f64_i64: BIN_EVAL( i64, lv->f64 != ( f64 )rv->i64 );
	neq_f64_f64: BIN_EVAL( i64, lv->f64 != rv->f64 );
	neq_f64_str: BIN_EVAL( i64, lv->f64 != ( f64 )rv->str->len );
	neq_str_i64: BIN_EVAL( i64, lv->str->len != rv->i64 );
	neq_str_f64: BIN_EVAL( i64, ( f64 )lv->str->len != rv->f64 );
	neq_str_str: BIN_EVAL( i64, lv->str != rv->str );

	lt_i64_i64: BIN_EVAL( i64, lv->i64 < rv->i64 );
	lt_i64_f64: BIN_EVAL( i64, ( f64 )lv->i64 < rv->f64 );
	lt_i64_str: BIN_EVAL( i64, lv->i64 < rv->str->len );
	lt_f64_i64: BIN_EVAL( i64, lv->f64 < ( f64 )rv->i64 );
	lt_f64_f64: BIN_EVAL( i64, lv->f64 < rv->f64 );
	lt_f64_str: BIN_EVAL( i64, lv->f64 < ( f64 )rv->str->len );
	lt_str_i64: BIN_EVAL( i64, lv->str->len < rv->i64 );
	lt_str_f64: BIN_EVAL( i64, ( f64 )lv->str->len < rv->f64 );
	lt_str_str: BIN_EVAL( i64, lv->str < rv->str );

	le_i64_i64: BIN_EVAL( i64, lv->i64 <= rv->i64 );
	le_i64_f64: BIN_EVAL( i64, ( f64 )lv->i64 <= rv->f64 );
	le_i64_str: BIN_EVAL( i64, lv->i64 <= rv->str->len );
	le_f64_i64: BIN_EVAL( i64, lv->f64 <= ( f64 )rv->i64 );
	le_f64_f64: BIN_EVAL( i64, lv->f64 <= rv->f64 );
	le_f64_str: BIN_EVAL( i64, lv->f64 <= ( f64 )rv->str->len );
	le_str_i64: BIN_EVAL( i64, lv->str->len <= rv->i64 );
	le_str_f64: BIN_EVAL( i64, ( f64 )lv->str->len <= rv->f64 );
	le_str_str: BIN_EVAL( i64, lv->str <= rv->str );

	gt_i64_i64: BIN_EVAL( i64, lv->i64 > rv->i64 );
	gt_i64_f64: BIN_EVAL( i64, ( f64 )lv->i64 > rv->f64 );
	gt_i64_str: BIN_EVAL( i64, lv->i64 > rv->str->len );
	gt_f64_i64: BIN_EVAL( i64, lv->f64 > ( f64 )rv->i64 );
	gt_f64_f64: BIN_EVAL( i64, lv->f64 > rv->f64 );
	gt_f64_str: BIN_EVAL( i64, lv->f64 > ( f64 )rv->str->len );
	gt_str_i64: BIN_EVAL( i64, lv->str->len > rv->i64 );
	gt_str_f64: BIN_EVAL( i64, ( f64 )lv->str->len > rv->f64 );
	gt_str_str: BIN_EVAL( i64, lv->str > rv->str );

	ge_i64_i64: BIN_EVAL( i64, lv->i64 >= rv->i64 );
	ge_i64_f64: BIN_EVAL( i64, ( f64 )lv->i64 >= rv->f64 );
	ge_i64_str: BIN_EVAL( i64, lv->i64 >= rv->str->len );
	ge_f64_i64: BIN_EVAL( i64, lv->f64 >= ( f64 )rv->i64 );
	ge_f64_f64: BIN_EVAL( i64, lv->f64 >= rv->f64 );
	ge_f64_str: BIN_EVAL( i64, lv->f64 >= ( f64 )rv->str->len );
	ge_str_i64: BIN_EVAL( i64, lv->str->len >= rv->i64 );
	ge_str_f64: BIN_EVAL( i64, ( f64 )lv->str->len >= rv->f64 );
	ge_str_str: BIN_EVAL( i64, lv->str >= rv->str );

	and_i64_i64: BIN_EVAL( i64, lv->i64 && rv->i64 );
	and_i64_f64: BIN_EVAL( i64, ( f64 )lv->i64 && rv->f64 );
	and_i64_str: BIN_EVAL( i64, lv->i64 && rv->str->len );
	and_f64_i64: BIN_EVAL( i64, lv->f64 && ( f64 )rv->i64 );
	and_f64_f64: BIN_EVAL( i64, lv->f64 && rv->f64 );
	and_f64_str: BIN_EVAL( i64, lv->f64 && ( f64 )rv->str->len );
	and_str_i64: BIN_EVAL( i64, lv->str->len && rv->i64 );
	and_str_f64: BIN_EVAL( i64, ( f64 )lv->str->len && rv->f64 );
	and_str_str: BIN_EVAL( i64, lv->str && rv->str );

	or_i64_i64: BIN_EVAL( i64, lv->i64 || rv->i64 );
	or_i64_f64: BIN_EVAL( i64, ( f64 )lv->i64 || rv->f64 );
	or_i64_str: BIN_EVAL( i64, lv->i64 || rv->str->len );
	or_f64_i64: BIN_EVAL( i64, lv->f64 || ( f64 )rv->i64 );
	or_f64_f64: BIN_EVAL( i64, lv->f64 || rv->f64 );
	or_f64_str: BIN_EVAL( i64, lv->f64 || ( f64 )rv->str->len );
	or_str_i64: BIN_EVAL( i64, lv->str->len || rv->i64 );
	or_str_f64: BIN_EVAL( i64, ( f64 )lv->str->len || rv->f64 );
	or_str_str: BIN_EVAL( i64, lv->str || rv->str );

	addeq_i64_i64: BIN_EVAL( i64, lv->i64 + rv->i64 );
	addeq_i64_f64: BIN_EVAL( f64, ( f64 )lv->i64 + rv->f64 );
	addeq_i64_str: BIN_EVAL( i64, lv->i64 + rv->str->len );
	addeq_f64_i64: BIN_EVAL( f64, lv->f64 + ( f64 )rv->i64 );
	addeq_f64_f64: BIN_EVAL( f64, lv->f64 + rv->f64 );
	addeq_f64_str: BIN_EVAL( f64, lv->f64 + ( f64 )rv->str->len );
	addeq_str_i64: BIN_EVAL( i64, lv->str->len + rv->i64 );
	addeq_str_f64: BIN_EVAL( f64, ( f64 )lv->str->len + rv->f64 );
	addeq_str_str: BIN_EVAL( i64, lv->str->len + rv->str->len );

	subeq_i64_i64: BIN_EVAL( i64, lv->i64 - rv->i64 );
	subeq_i64_f64: BIN_EVAL( f64, ( f64 )lv->i64 - rv->f64 );
	subeq_i64_str: BIN_EVAL( i64, lv->i64 - rv->str->len );
	subeq_f64_i64: BIN_EVAL( f64, lv->f64 - ( f64 )rv->i64 );
	subeq_f64_f64: BIN_EVAL( f64, lv->f64 - rv->f64 );
	subeq_f64_str: BIN_EVAL( f64, lv->f64 - ( f64 )rv->str->len );
	subeq_str_i64: BIN_EVAL( i64, lv->str->len - rv->i64 );
	subeq_str_f64: BIN_EVAL( f64, ( f64 )lv->str->len - rv->f64 );
	subeq_str_str: BIN_EVAL( i64, lv->str->len - rv->str->len );

	muleq_i64_i64: BIN_EVAL( i64, lv->i64 * rv->i64 );
	muleq_i64_f64: BIN_EVAL( f64, ( f64 )lv->i64 * rv->f64 );
	muleq_i64_str: BIN_EVAL( i64, lv->i64 * rv->str->len );
	muleq_f64_i64: BIN_EVAL( f64, lv->f64 * ( f64 )rv->i64 );
	muleq_f64_f64: BIN_EVAL( f64, lv->f64 * rv->f64 );
	muleq_f64_str: BIN_EVAL( f64, lv->f64 * ( f64 )rv->str->len );
	muleq_str_i64: BIN_EVAL( i64, lv->str->len * rv->i64 );
	muleq_str_f64: BIN_EVAL( f64, ( f64 )lv->str->len * rv->f64 );
	muleq_str_str: BIN_EVAL( i64, lv->str->len * rv->str->len );

	diveq_i64_i64: BIN_EVAL( i64, lv->i64 / rv->i64 );
	diveq_i64_f64: BIN_EVAL( f64, ( f64 )lv->i64 / rv->f64 );
	diveq_i64_str: BIN_EVAL( i64, lv->i64 / rv->str->len );
	diveq_f64_i64: BIN_EVAL( f64, lv->f64 / ( f64 )rv->i64 );
	diveq_f64_f64: BIN_EVAL( f64, lv->f64 / rv->f64 );
	diveq_f64_str: BIN_EVAL( f64, lv->f64 / ( f64 )rv->str->len );
	diveq_str_i64: BIN_EVAL( i64, lv->str->len / rv->i64 );
	diveq_str_f64: BIN_EVAL( f64, ( f64 )lv->str->len / rv->f64 );
	diveq_str_str: BIN_EVAL( i64, lv->str->len / rv->str->len );

	modeq_i64_i64: BIN_EVAL( i64, lv->i64 % rv->i64 );
	modeq_i64_f64: BIN_EVAL( i64, lv->i64 % ( i64 )rv->f64 );
	modeq_i64_str: BIN_EVAL( i64, lv->i64 % rv->str->len );
	modeq_f64_i64: BIN_EVAL( i64, ( i64 )lv->f64 % rv->i64 );
	modeq_f64_f64: BIN_EVAL( i64, ( i64 )lv->f64 % ( i64 )rv->f64 );
	modeq_f64_str: BIN_EVAL( i64, ( i64 )lv->f64 % rv->str->len );
	modeq_str_i64: BIN_EVAL( i64, lv->str->len % rv->i64 );
	modeq_str_f64: BIN_EVAL( i64, lv->str->len % ( i64 )rv->f64 );
	modeq_str_str: BIN_EVAL( i64, lv->str->len % rv->str->len );

	bandeq_i64_i64: BIN_EVAL( i64, lv->i64 & rv->i64 );
	bandeq_i64_f64: BIN_EVAL( i64, lv->i64 & ( i64 )rv->f64 );
	bandeq_i64_str: BIN_EVAL( i64, lv->i64 & rv->str->len );
	bandeq_f64_i64: BIN_EVAL( i64, ( i64 )lv->f64 & rv->i64 );
	bandeq_f64_f64: BIN_EVAL( i64, ( i64 )lv->f64 & ( i64 )rv->f64 );
	bandeq_f64_str: BIN_EVAL( i64, ( i64 )lv->f64 & rv->str->len );
	bandeq_str_i64: BIN_EVAL( i64, lv->str->len & rv->i64 );
	bandeq_str_f64: BIN_EVAL( i64, lv->str->len & ( i64 )rv->f64 );
	bandeq_str_str: BIN_EVAL( i64, lv->str->len & rv->str->len );

	boreq_i64_i64: BIN_EVAL( i64, lv->i64 | rv->i64 );
	boreq_i64_f64: BIN_EVAL( i64, lv->i64 | ( i64 )rv->f64 );
	boreq_i64_str: BIN_EVAL( i64, lv->i64 | rv->str->len );
	boreq_f64_i64: BIN_EVAL( i64, ( i64 )lv->f64 | rv->i64 );
	boreq_f64_f64: BIN_EVAL( i64, ( i64 )lv->f64 | ( i64 )rv->f64 );
	boreq_f64_str: BIN_EVAL( i64, ( i64 )lv->f64 | rv->str->len );
	boreq_str_i64: BIN_EVAL( i64, lv->str->len | rv->i64 );
	boreq_str_f64: BIN_EVAL( i64, lv->str->len | ( i64 )rv->f64 );
	boreq_str_str: BIN_EVAL( i64, lv->str->len | rv->str->len );

	bxoreq_i64_i64: BIN_EVAL( i64, lv->i64 ^ rv->i64 );
	bxoreq_i64_f64: BIN_EVAL( i64, lv->i64 ^ ( i64 )rv->f64 );
	bxoreq_i64_str: BIN_EVAL( i64, lv->i64 ^ rv->str->len );
	bxoreq_f64_i64: BIN_EVAL( i64, ( i64 )lv->f64 ^ rv->i64 );
	bxoreq_f64_f64: BIN_EVAL( i64, ( i64 )lv->f64 ^ ( i64 )rv->f64 );
	bxoreq_f64_str: BIN_EVAL( i64, ( i64 )lv->f64 ^ rv->str->len );
	bxoreq_str_i64: BIN_EVAL( i64, lv->str->len ^ rv->i64 );
	bxoreq_str_f64: BIN_EVAL( i64, lv->str->len ^ ( i64 )rv->f64 );
	bxoreq_str_str: BIN_EVAL( i64, lv->str->len ^ rv->str->len );

	lsheq_i64_i64: BIN_EVAL( i64, lv->i64 << rv->i64 );
	lsheq_i64_f64: BIN_EVAL( i64, lv->i64 << ( i64 )rv->f64 );
	lsheq_i64_str: BIN_EVAL( i64, lv->i64 << rv->str->len );
	lsheq_f64_i64: BIN_EVAL( i64, ( i64 )lv->f64 << rv->i64 );
	lsheq_f64_f64: BIN_EVAL( i64, ( i64 )lv->f64 << ( i64 )rv->f64 );
	lsheq_f64_str: BIN_EVAL( i64, ( i64 )lv->f64 << rv->str->len );
	lsheq_str_i64: BIN_EVAL( i64, lv->str->len << rv->i64 );
	lsheq_str_f64: BIN_EVAL( i64, lv->str->len << ( i64 )rv->f64 );
	lsheq_str_str: BIN_EVAL( i64, lv->str->len << rv->str->len );

	rsheq_i64_i64: BIN_EVAL( i64, lv->i64 >> rv->i64 );
	rsheq_i64_f64: BIN_EVAL( i64, lv->i64 >> ( i64 )rv->f64 );
	rsheq_i64_str: BIN_EVAL( i64, lv->i64 >> rv->str->len );
	rsheq_f64_i64: BIN_EVAL( i64, ( i64 )lv->f64 >> rv->i64 );
	rsheq_f64_f64: BIN_EVAL( i64, ( i64 )lv->f64 >> ( i64 )rv->f64 );
	rsheq_f64_str: BIN_EVAL( i64, ( i64 )lv->f64 >> rv->str->len );
	rsheq_str_i64: BIN_EVAL( i64, lv->str->len >> rv->i64 );
	rsheq_str_f64: BIN_EVAL( i64, lv->str->len >> ( i64 )rv->f64 );
	rsheq_str_str: BIN_EVAL( i64, lv->str->len >> rv->str->len );
}

void binary_compile( compiler* compiler, parser* parser )
{
	// static void* ops[ tk_n ][ tk_n ] = { };
	ir* rhs = vec_pop( parser->irs );
	ir* op = vec_pop( parser->irs );
	ir* lhs = vec_pop( parser->irs );
	ir* out = vec_commit( parser->irs );
	opcode oc = op->value.i64;
	if( binary_foldable( lhs, rhs ) ){ return binary_fold( out, lhs, oc, rhs ); }
	/* emit here. write to out if needed. */
}