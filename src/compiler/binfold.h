#ifndef BS_BINFOLD_H
#define BS_BINFOLD_H
/* Auto generates all the labels for us. */
/* They help ensure we never miss a permutation, since C will yell at us. */
#define X_BIN_LBL3( OP, ENUM ) &&OP##ENUM,

#define X_BIN_LBL2( OP, ENUM )\
	{ VALUE_TYPES2( OP, ENUM##_, X_BIN_LBL3 ) },

#define X_BIN_LBL( TK, OP )\
	{ VALUE_TYPES( OP##_, , X_BIN_LBL2 ) },

/* I dont usually like macros that make debugging difficult, */
/* but this is a brevity exception. */
#define BIN_EVAL( T, V ) out->value_type = value_##T; out->T = V; return;

u8 bin_foldable( ir* lhs, ir* rhs )
{
	return lhs->ir_type == ir_const && rhs->ir_type == ir_const;
}

void bin_fold( ir* out, ir* l, ir* op, ir* r )
{
	static const void* ops[ ][ value_n ][ value_n ] = { OP_BIN( , X_BIN_LBL ) };
	out->ir_type = ir_const;
	opcode opcode = op->opcode - op_add;
	goto *ops[ opcode ][ l->value_type ][ r->value_type ];

	add_i64_i64: BIN_EVAL( i64, l->i64 + r->i64 );
	add_i64_f64: BIN_EVAL( f64, ( f64 )l->i64 + r->f64 );
	add_i64_str: BIN_EVAL( i64, l->i64 + r->str->len );
	add_f64_i64: BIN_EVAL( f64, l->f64 + ( f64 )r->i64 );
	add_f64_f64: BIN_EVAL( f64, l->f64 + r->f64 );
	add_f64_str: BIN_EVAL( f64, l->f64 + ( f64 )r->str->len );
	add_str_i64: BIN_EVAL( i64, l->str->len + r->i64 );
	add_str_f64: BIN_EVAL( f64, ( f64 )l->str->len + r->f64 );
	add_str_str: BIN_EVAL( i64, l->str->len + r->str->len );

	sub_i64_i64: BIN_EVAL( i64, l->i64 - r->i64 );
	sub_i64_f64: BIN_EVAL( f64, ( f64 )l->i64 - r->f64 );
	sub_i64_str: BIN_EVAL( i64, l->i64 - r->str->len );
	sub_f64_i64: BIN_EVAL( f64, l->f64 - ( f64 )r->i64 );
	sub_f64_f64: BIN_EVAL( f64, l->f64 - r->f64 );
	sub_f64_str: BIN_EVAL( f64, l->f64 - ( f64 )r->str->len );
	sub_str_i64: BIN_EVAL( i64, l->str->len - r->i64 );
	sub_str_f64: BIN_EVAL( f64, ( f64 )l->str->len - r->f64 );
	sub_str_str: BIN_EVAL( i64, l->str->len - r->str->len );

	mul_i64_i64: BIN_EVAL( i64, l->i64 * r->i64 );
	mul_i64_f64: BIN_EVAL( f64, ( f64 )l->i64 * r->f64 );
	mul_i64_str: BIN_EVAL( i64, l->i64 * r->str->len );
	mul_f64_i64: BIN_EVAL( f64, l->f64 * ( f64 )r->i64 );
	mul_f64_f64: BIN_EVAL( f64, l->f64 * r->f64 );
	mul_f64_str: BIN_EVAL( f64, l->f64 * ( f64 )r->str->len );
	mul_str_i64: BIN_EVAL( i64, l->str->len * r->i64 );
	mul_str_f64: BIN_EVAL( f64, ( f64 )l->str->len * r->f64 );
	mul_str_str: BIN_EVAL( i64, l->str->len * r->str->len );

	div_i64_i64: BIN_EVAL( i64, l->i64 / r->i64 );
	div_i64_f64: BIN_EVAL( f64, ( f64 )l->i64 / r->f64 );
	div_i64_str: BIN_EVAL( i64, l->i64 / r->str->len );
	div_f64_i64: BIN_EVAL( f64, l->f64 / ( f64 )r->i64 );
	div_f64_f64: BIN_EVAL( f64, l->f64 / r->f64 );
	div_f64_str: BIN_EVAL( f64, l->f64 / ( f64 )r->str->len );
	div_str_i64: BIN_EVAL( i64, l->str->len / r->i64 );
	div_str_f64: BIN_EVAL( f64, ( f64 )l->str->len / r->f64 );
	div_str_str: BIN_EVAL( i64, l->str->len / r->str->len );

	mod_i64_i64: BIN_EVAL( i64, l->i64 % r->i64 );
	mod_i64_f64: BIN_EVAL( i64, l->i64 % ( i64 )r->f64 );
	mod_i64_str: BIN_EVAL( i64, l->i64 % r->str->len );
	mod_f64_i64: BIN_EVAL( i64, ( i64 )l->f64 % r->i64 );
	mod_f64_f64: BIN_EVAL( i64, ( i64 )l->f64 % ( i64 )r->f64 );
	mod_f64_str: BIN_EVAL( i64, ( i64 )l->f64 % r->str->len );
	mod_str_i64: BIN_EVAL( i64, l->str->len % r->i64 );
	mod_str_f64: BIN_EVAL( i64, l->str->len % ( i64 )r->f64 );
	mod_str_str: BIN_EVAL( i64, l->str->len % r->str->len );

	pow_i64_i64: BIN_EVAL( f64, pow( ( f64 )l->i64, ( f64 )r->i64 ) );
	pow_i64_f64: BIN_EVAL( f64, pow( ( f64 )l->i64, r->f64 ) );
	pow_i64_str: BIN_EVAL( f64, pow( ( f64 )l->i64, ( f64 )r->str->len ) );
	pow_f64_i64: BIN_EVAL( f64, pow( l->f64, ( f64 )r->i64 ) );
	pow_f64_f64: BIN_EVAL( f64, pow( l->f64, r->f64 ) );
	pow_f64_str: BIN_EVAL( f64, pow( l->f64, ( f64 )r->str->len ) );
	pow_str_i64: BIN_EVAL( f64, pow( ( f64 )l->str->len, ( f64 )r->i64 ) );
	pow_str_f64: BIN_EVAL( f64, pow( ( f64 )l->str->len, r->f64 ) );
	pow_str_str: BIN_EVAL( f64, pow( ( f64 )l->str->len, ( f64 )r->str->len ) );

	band_i64_i64: BIN_EVAL( i64, l->i64 & r->i64 );
	band_i64_f64: BIN_EVAL( i64, l->i64 & ( i64 )r->f64 );
	band_i64_str: BIN_EVAL( i64, l->i64 & r->str->len );
	band_f64_i64: BIN_EVAL( i64, ( i64 )l->f64 & r->i64 );
	band_f64_f64: BIN_EVAL( i64, ( i64 )l->f64 & ( i64 )r->f64 );
	band_f64_str: BIN_EVAL( i64, ( i64 )l->f64 & r->str->len );
	band_str_i64: BIN_EVAL( i64, l->str->len & r->i64 );
	band_str_f64: BIN_EVAL( i64, l->str->len & ( i64 )r->f64 );
	band_str_str: BIN_EVAL( i64, l->str->len & r->str->len );

	bor_i64_i64: BIN_EVAL( i64, l->i64 | r->i64 );
	bor_i64_f64: BIN_EVAL( i64, l->i64 | ( i64 )r->f64 );
	bor_i64_str: BIN_EVAL( i64, l->i64 | r->str->len );
	bor_f64_i64: BIN_EVAL( i64, ( i64 )l->f64 | r->i64 );
	bor_f64_f64: BIN_EVAL( i64, ( i64 )l->f64 | ( i64 )r->f64 );
	bor_f64_str: BIN_EVAL( i64, ( i64 )l->f64 | r->str->len );
	bor_str_i64: BIN_EVAL( i64, l->str->len | r->i64 );
	bor_str_f64: BIN_EVAL( i64, l->str->len | ( i64 )r->f64 );
	bor_str_str: BIN_EVAL( i64, l->str->len | r->str->len );

	bxor_i64_i64: BIN_EVAL( i64, l->i64 ^ r->i64 );
	bxor_i64_f64: BIN_EVAL( i64, l->i64 ^ ( i64 )r->f64 );
	bxor_i64_str: BIN_EVAL( i64, l->i64 ^ r->str->len );
	bxor_f64_i64: BIN_EVAL( i64, ( i64 )l->f64 ^ r->i64 );
	bxor_f64_f64: BIN_EVAL( i64, ( i64 )l->f64 ^ ( i64 )r->f64 );
	bxor_f64_str: BIN_EVAL( i64, ( i64 )l->f64 ^ r->str->len );
	bxor_str_i64: BIN_EVAL( i64, l->str->len ^ r->i64 );
	bxor_str_f64: BIN_EVAL( i64, l->str->len ^ ( i64 )r->f64 );
	bxor_str_str: BIN_EVAL( i64, l->str->len ^ r->str->len );

	lsh_i64_i64: BIN_EVAL( i64, l->i64 << r->i64 );
	lsh_i64_f64: BIN_EVAL( i64, l->i64 << ( i64 )r->f64 );
	lsh_i64_str: BIN_EVAL( i64, l->i64 << r->str->len );
	lsh_f64_i64: BIN_EVAL( i64, ( i64 )l->f64 << r->i64 );
	lsh_f64_f64: BIN_EVAL( i64, ( i64 )l->f64 << ( i64 )r->f64 );
	lsh_f64_str: BIN_EVAL( i64, ( i64 )l->f64 << r->str->len );
	lsh_str_i64: BIN_EVAL( i64, l->str->len << r->i64 );
	lsh_str_f64: BIN_EVAL( i64, l->str->len << ( i64 )r->f64 );
	lsh_str_str: BIN_EVAL( i64, l->str->len << r->str->len );

	rsh_i64_i64: BIN_EVAL( i64, l->i64 >> r->i64 );
	rsh_i64_f64: BIN_EVAL( i64, l->i64 >> ( i64 )r->f64 );
	rsh_i64_str: BIN_EVAL( i64, l->i64 >> r->str->len );
	rsh_f64_i64: BIN_EVAL( i64, ( i64 )l->f64 >> r->i64 );
	rsh_f64_f64: BIN_EVAL( i64, ( i64 )l->f64 >> ( i64 )r->f64 );
	rsh_f64_str: BIN_EVAL( i64, ( i64 )l->f64 >> r->str->len );
	rsh_str_i64: BIN_EVAL( i64, l->str->len >> r->i64 );
	rsh_str_f64: BIN_EVAL( i64, l->str->len >> ( i64 )r->f64 );
	rsh_str_str: BIN_EVAL( i64, l->str->len >> r->str->len );

	eqeq_i64_i64: BIN_EVAL( i64, l->i64 == r->i64 );
	eqeq_i64_f64: BIN_EVAL( i64, ( f64 )l->i64 == r->f64 );
	eqeq_i64_str: BIN_EVAL( i64, l->i64 == r->str->len );
	eqeq_f64_i64: BIN_EVAL( i64, l->f64 == ( f64 )r->i64 );
	eqeq_f64_f64: BIN_EVAL( i64, l->f64 == r->f64 );
	eqeq_f64_str: BIN_EVAL( i64, l->f64 == ( f64 )r->str->len );
	eqeq_str_i64: BIN_EVAL( i64, l->str->len == r->i64 );
	eqeq_str_f64: BIN_EVAL( i64, ( f64 )l->str->len == r->f64 );
	eqeq_str_str: BIN_EVAL( i64, l->str == r->str );

	neq_i64_i64: BIN_EVAL( i64, l->i64 != r->i64 );
	neq_i64_f64: BIN_EVAL( i64, ( f64 )l->i64 != r->f64 );
	neq_i64_str: BIN_EVAL( i64, l->i64 != r->str->len );
	neq_f64_i64: BIN_EVAL( i64, l->f64 != ( f64 )r->i64 );
	neq_f64_f64: BIN_EVAL( i64, l->f64 != r->f64 );
	neq_f64_str: BIN_EVAL( i64, l->f64 != ( f64 )r->str->len );
	neq_str_i64: BIN_EVAL( i64, l->str->len != r->i64 );
	neq_str_f64: BIN_EVAL( i64, ( f64 )l->str->len != r->f64 );
	neq_str_str: BIN_EVAL( i64, l->str != r->str );

	lt_i64_i64: BIN_EVAL( i64, l->i64 < r->i64 );
	lt_i64_f64: BIN_EVAL( i64, ( f64 )l->i64 < r->f64 );
	lt_i64_str: BIN_EVAL( i64, l->i64 < r->str->len );
	lt_f64_i64: BIN_EVAL( i64, l->f64 < ( f64 )r->i64 );
	lt_f64_f64: BIN_EVAL( i64, l->f64 < r->f64 );
	lt_f64_str: BIN_EVAL( i64, l->f64 < ( f64 )r->str->len );
	lt_str_i64: BIN_EVAL( i64, l->str->len < r->i64 );
	lt_str_f64: BIN_EVAL( i64, ( f64 )l->str->len < r->f64 );
	lt_str_str: BIN_EVAL( i64, l->str < r->str );

	le_i64_i64: BIN_EVAL( i64, l->i64 <= r->i64 );
	le_i64_f64: BIN_EVAL( i64, ( f64 )l->i64 <= r->f64 );
	le_i64_str: BIN_EVAL( i64, l->i64 <= r->str->len );
	le_f64_i64: BIN_EVAL( i64, l->f64 <= ( f64 )r->i64 );
	le_f64_f64: BIN_EVAL( i64, l->f64 <= r->f64 );
	le_f64_str: BIN_EVAL( i64, l->f64 <= ( f64 )r->str->len );
	le_str_i64: BIN_EVAL( i64, l->str->len <= r->i64 );
	le_str_f64: BIN_EVAL( i64, ( f64 )l->str->len <= r->f64 );
	le_str_str: BIN_EVAL( i64, l->str <= r->str );

	gt_i64_i64: BIN_EVAL( i64, l->i64 > r->i64 );
	gt_i64_f64: BIN_EVAL( i64, ( f64 )l->i64 > r->f64 );
	gt_i64_str: BIN_EVAL( i64, l->i64 > r->str->len );
	gt_f64_i64: BIN_EVAL( i64, l->f64 > ( f64 )r->i64 );
	gt_f64_f64: BIN_EVAL( i64, l->f64 > r->f64 );
	gt_f64_str: BIN_EVAL( i64, l->f64 > ( f64 )r->str->len );
	gt_str_i64: BIN_EVAL( i64, l->str->len > r->i64 );
	gt_str_f64: BIN_EVAL( i64, ( f64 )l->str->len > r->f64 );
	gt_str_str: BIN_EVAL( i64, l->str > r->str );

	ge_i64_i64: BIN_EVAL( i64, l->i64 >= r->i64 );
	ge_i64_f64: BIN_EVAL( i64, ( f64 )l->i64 >= r->f64 );
	ge_i64_str: BIN_EVAL( i64, l->i64 >= r->str->len );
	ge_f64_i64: BIN_EVAL( i64, l->f64 >= ( f64 )r->i64 );
	ge_f64_f64: BIN_EVAL( i64, l->f64 >= r->f64 );
	ge_f64_str: BIN_EVAL( i64, l->f64 >= ( f64 )r->str->len );
	ge_str_i64: BIN_EVAL( i64, l->str->len >= r->i64 );
	ge_str_f64: BIN_EVAL( i64, ( f64 )l->str->len >= r->f64 );
	ge_str_str: BIN_EVAL( i64, l->str >= r->str );

	and_i64_i64: BIN_EVAL( i64, l->i64 && r->i64 );
	and_i64_f64: BIN_EVAL( i64, ( f64 )l->i64 && r->f64 );
	and_i64_str: BIN_EVAL( i64, l->i64 && r->str->len );
	and_f64_i64: BIN_EVAL( i64, l->f64 && ( f64 )r->i64 );
	and_f64_f64: BIN_EVAL( i64, l->f64 && r->f64 );
	and_f64_str: BIN_EVAL( i64, l->f64 && ( f64 )r->str->len );
	and_str_i64: BIN_EVAL( i64, l->str->len && r->i64 );
	and_str_f64: BIN_EVAL( i64, ( f64 )l->str->len && r->f64 );
	and_str_str: BIN_EVAL( i64, l->str && r->str );

	or_i64_i64: BIN_EVAL( i64, l->i64 || r->i64 );
	or_i64_f64: BIN_EVAL( i64, ( f64 )l->i64 || r->f64 );
	or_i64_str: BIN_EVAL( i64, l->i64 || r->str->len );
	or_f64_i64: BIN_EVAL( i64, l->f64 || ( f64 )r->i64 );
	or_f64_f64: BIN_EVAL( i64, l->f64 || r->f64 );
	or_f64_str: BIN_EVAL( i64, l->f64 || ( f64 )r->str->len );
	or_str_i64: BIN_EVAL( i64, l->str->len || r->i64 );
	or_str_f64: BIN_EVAL( i64, ( f64 )l->str->len || r->f64 );
	or_str_str: BIN_EVAL( i64, l->str || r->str );

	addeq_i64_i64: BIN_EVAL( i64, l->i64 + r->i64 );
	addeq_i64_f64: BIN_EVAL( f64, ( f64 )l->i64 + r->f64 );
	addeq_i64_str: BIN_EVAL( i64, l->i64 + r->str->len );
	addeq_f64_i64: BIN_EVAL( f64, l->f64 + ( f64 )r->i64 );
	addeq_f64_f64: BIN_EVAL( f64, l->f64 + r->f64 );
	addeq_f64_str: BIN_EVAL( f64, l->f64 + ( f64 )r->str->len );
	addeq_str_i64: BIN_EVAL( i64, l->str->len + r->i64 );
	addeq_str_f64: BIN_EVAL( f64, ( f64 )l->str->len + r->f64 );
	addeq_str_str: BIN_EVAL( i64, l->str->len + r->str->len );

	subeq_i64_i64: BIN_EVAL( i64, l->i64 - r->i64 );
	subeq_i64_f64: BIN_EVAL( f64, ( f64 )l->i64 - r->f64 );
	subeq_i64_str: BIN_EVAL( i64, l->i64 - r->str->len );
	subeq_f64_i64: BIN_EVAL( f64, l->f64 - ( f64 )r->i64 );
	subeq_f64_f64: BIN_EVAL( f64, l->f64 - r->f64 );
	subeq_f64_str: BIN_EVAL( f64, l->f64 - ( f64 )r->str->len );
	subeq_str_i64: BIN_EVAL( i64, l->str->len - r->i64 );
	subeq_str_f64: BIN_EVAL( f64, ( f64 )l->str->len - r->f64 );
	subeq_str_str: BIN_EVAL( i64, l->str->len - r->str->len );

	muleq_i64_i64: BIN_EVAL( i64, l->i64 * r->i64 );
	muleq_i64_f64: BIN_EVAL( f64, ( f64 )l->i64 * r->f64 );
	muleq_i64_str: BIN_EVAL( i64, l->i64 * r->str->len );
	muleq_f64_i64: BIN_EVAL( f64, l->f64 * ( f64 )r->i64 );
	muleq_f64_f64: BIN_EVAL( f64, l->f64 * r->f64 );
	muleq_f64_str: BIN_EVAL( f64, l->f64 * ( f64 )r->str->len );
	muleq_str_i64: BIN_EVAL( i64, l->str->len * r->i64 );
	muleq_str_f64: BIN_EVAL( f64, ( f64 )l->str->len * r->f64 );
	muleq_str_str: BIN_EVAL( i64, l->str->len * r->str->len );

	diveq_i64_i64: BIN_EVAL( i64, l->i64 / r->i64 );
	diveq_i64_f64: BIN_EVAL( f64, ( f64 )l->i64 / r->f64 );
	diveq_i64_str: BIN_EVAL( i64, l->i64 / r->str->len );
	diveq_f64_i64: BIN_EVAL( f64, l->f64 / ( f64 )r->i64 );
	diveq_f64_f64: BIN_EVAL( f64, l->f64 / r->f64 );
	diveq_f64_str: BIN_EVAL( f64, l->f64 / ( f64 )r->str->len );
	diveq_str_i64: BIN_EVAL( i64, l->str->len / r->i64 );
	diveq_str_f64: BIN_EVAL( f64, ( f64 )l->str->len / r->f64 );
	diveq_str_str: BIN_EVAL( i64, l->str->len / r->str->len );

	modeq_i64_i64: BIN_EVAL( i64, l->i64 % r->i64 );
	modeq_i64_f64: BIN_EVAL( i64, l->i64 % ( i64 )r->f64 );
	modeq_i64_str: BIN_EVAL( i64, l->i64 % r->str->len );
	modeq_f64_i64: BIN_EVAL( i64, ( i64 )l->f64 % r->i64 );
	modeq_f64_f64: BIN_EVAL( i64, ( i64 )l->f64 % ( i64 )r->f64 );
	modeq_f64_str: BIN_EVAL( i64, ( i64 )l->f64 % r->str->len );
	modeq_str_i64: BIN_EVAL( i64, l->str->len % r->i64 );
	modeq_str_f64: BIN_EVAL( i64, l->str->len % ( i64 )r->f64 );
	modeq_str_str: BIN_EVAL( i64, l->str->len % r->str->len );

	bandeq_i64_i64: BIN_EVAL( i64, l->i64 & r->i64 );
	bandeq_i64_f64: BIN_EVAL( i64, l->i64 & ( i64 )r->f64 );
	bandeq_i64_str: BIN_EVAL( i64, l->i64 & r->str->len );
	bandeq_f64_i64: BIN_EVAL( i64, ( i64 )l->f64 & r->i64 );
	bandeq_f64_f64: BIN_EVAL( i64, ( i64 )l->f64 & ( i64 )r->f64 );
	bandeq_f64_str: BIN_EVAL( i64, ( i64 )l->f64 & r->str->len );
	bandeq_str_i64: BIN_EVAL( i64, l->str->len & r->i64 );
	bandeq_str_f64: BIN_EVAL( i64, l->str->len & ( i64 )r->f64 );
	bandeq_str_str: BIN_EVAL( i64, l->str->len & r->str->len );

	boreq_i64_i64: BIN_EVAL( i64, l->i64 | r->i64 );
	boreq_i64_f64: BIN_EVAL( i64, l->i64 | ( i64 )r->f64 );
	boreq_i64_str: BIN_EVAL( i64, l->i64 | r->str->len );
	boreq_f64_i64: BIN_EVAL( i64, ( i64 )l->f64 | r->i64 );
	boreq_f64_f64: BIN_EVAL( i64, ( i64 )l->f64 | ( i64 )r->f64 );
	boreq_f64_str: BIN_EVAL( i64, ( i64 )l->f64 | r->str->len );
	boreq_str_i64: BIN_EVAL( i64, l->str->len | r->i64 );
	boreq_str_f64: BIN_EVAL( i64, l->str->len | ( i64 )r->f64 );
	boreq_str_str: BIN_EVAL( i64, l->str->len | r->str->len );

	bxoreq_i64_i64: BIN_EVAL( i64, l->i64 ^ r->i64 );
	bxoreq_i64_f64: BIN_EVAL( i64, l->i64 ^ ( i64 )r->f64 );
	bxoreq_i64_str: BIN_EVAL( i64, l->i64 ^ r->str->len );
	bxoreq_f64_i64: BIN_EVAL( i64, ( i64 )l->f64 ^ r->i64 );
	bxoreq_f64_f64: BIN_EVAL( i64, ( i64 )l->f64 ^ ( i64 )r->f64 );
	bxoreq_f64_str: BIN_EVAL( i64, ( i64 )l->f64 ^ r->str->len );
	bxoreq_str_i64: BIN_EVAL( i64, l->str->len ^ r->i64 );
	bxoreq_str_f64: BIN_EVAL( i64, l->str->len ^ ( i64 )r->f64 );
	bxoreq_str_str: BIN_EVAL( i64, l->str->len ^ r->str->len );

	lsheq_i64_i64: BIN_EVAL( i64, l->i64 << r->i64 );
	lsheq_i64_f64: BIN_EVAL( i64, l->i64 << ( i64 )r->f64 );
	lsheq_i64_str: BIN_EVAL( i64, l->i64 << r->str->len );
	lsheq_f64_i64: BIN_EVAL( i64, ( i64 )l->f64 << r->i64 );
	lsheq_f64_f64: BIN_EVAL( i64, ( i64 )l->f64 << ( i64 )r->f64 );
	lsheq_f64_str: BIN_EVAL( i64, ( i64 )l->f64 << r->str->len );
	lsheq_str_i64: BIN_EVAL( i64, l->str->len << r->i64 );
	lsheq_str_f64: BIN_EVAL( i64, l->str->len << ( i64 )r->f64 );
	lsheq_str_str: BIN_EVAL( i64, l->str->len << r->str->len );

	rsheq_i64_i64: BIN_EVAL( i64, l->i64 >> r->i64 );
	rsheq_i64_f64: BIN_EVAL( i64, l->i64 >> ( i64 )r->f64 );
	rsheq_i64_str: BIN_EVAL( i64, l->i64 >> r->str->len );
	rsheq_f64_i64: BIN_EVAL( i64, ( i64 )l->f64 >> r->i64 );
	rsheq_f64_f64: BIN_EVAL( i64, ( i64 )l->f64 >> ( i64 )r->f64 );
	rsheq_f64_str: BIN_EVAL( i64, ( i64 )l->f64 >> r->str->len );
	rsheq_str_i64: BIN_EVAL( i64, l->str->len >> r->i64 );
	rsheq_str_f64: BIN_EVAL( i64, l->str->len >> ( i64 )r->f64 );
	rsheq_str_str: BIN_EVAL( i64, l->str->len >> r->str->len );

}

#endif