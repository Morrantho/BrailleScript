Value EvalBinErr( Value *lhs, OpCode op, Value *rhs )
{
	Throw( "Illegal Binary Operation: %d", op );
	return ( Value ){ 0 };
}

Value EvalAdd( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, lhs->i64 + rhs->i64 );
	F64: return VALUE( F64, f64, lhs->f64 + rhs->f64 );
	STR: return VALUE( I64, i64, lhs->str->len + rhs->str->len );
}

Value EvalSub( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, lhs->i64 - rhs->i64 );
	F64: return VALUE( F64, f64, lhs->f64 - rhs->f64 );
	STR: return VALUE( I64, i64, lhs->str->len - rhs->str->len );
}

Value EvalMul( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, lhs->i64 * rhs->i64 );
	F64: return VALUE( F64, f64, lhs->f64 * rhs->f64 );
	STR: return VALUE( I64, i64, lhs->str->len * rhs->str->len );
}

Value EvalDiv( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, lhs->i64 / rhs->i64 );
	F64: return VALUE( F64, f64, lhs->f64 / rhs->f64 );
	STR: return VALUE( I64, i64, lhs->str->len / rhs->str->len );
}

Value EvalMod( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, lhs->i64 % rhs->i64 );
	F64: return VALUE( F64, f64, ( I64 )lhs->f64 % ( I64 )rhs->f64 );
	STR: return VALUE( I64, i64, lhs->str->len % rhs->str->len );
}

Value EvalPow( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, ( I64 )pow( ( F64 )lhs->i64, ( F64 )rhs->i64 ) );
	F64: return VALUE( F64, f64, pow( lhs->f64, rhs->f64 ) );
	STR: return VALUE( I64, i64, ( I64 )pow( ( F64 )lhs->str->len, ( F64 )rhs->str->len ) );
}

Value EvalBand( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, lhs->i64 & rhs->i64 );
	F64: return VALUE( F64, f64, ( I64 )lhs->f64 & ( I64 )rhs->f64 );
	STR: return VALUE( I64, i64, lhs->str->len & rhs->str->len );
}

Value EvalBor( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, lhs->i64 | rhs->i64 );
	F64: return VALUE( F64, f64, ( I64 )lhs->f64 | ( I64 )rhs->f64 );
	STR: return VALUE( I64, i64, lhs->str->len | rhs->str->len );
}

Value EvalBxor( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, lhs->i64 ^ rhs->i64 );
	F64: return VALUE( F64, f64, ( I64 )lhs->f64 ^ ( I64 )rhs->f64 );
	STR: return VALUE( I64, i64, lhs->str->len ^ rhs->str->len );
}

Value EvalLsh( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, lhs->i64 << rhs->i64 );
	F64: return VALUE( F64, f64, ( I64 )lhs->f64 << ( I64 )rhs->f64 );
	STR: return VALUE( I64, i64, lhs->str->len << rhs->str->len );
}

Value EvalRsh( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, lhs->i64 >> rhs->i64 );
	F64: return VALUE( F64, f64, ( I64 )lhs->f64 >> ( I64 )rhs->f64 );
	STR: return VALUE( I64, i64, lhs->str->len >> rhs->str->len );
}

Value EvalEqEq( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, lhs->i64 == rhs->i64 );
	F64: return VALUE( F64, f64, lhs->f64 == rhs->f64 );
	STR: return VALUE( I64, i64, lhs->str == rhs->str );
}

Value EvalNeq( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, lhs->i64 != rhs->i64 );
	F64: return VALUE( F64, f64, lhs->f64 != rhs->f64 );
	STR: return VALUE( I64, i64, lhs->str != rhs->str );
}

Value EvalLt( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, lhs->i64 < rhs->i64 );
	F64: return VALUE( F64, f64, lhs->f64 < rhs->f64 );
	STR: return VALUE( I64, i64, lhs->str->len < rhs->str->len );
}

Value EvalLe( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, lhs->i64 <= rhs->i64 );
	F64: return VALUE( F64, f64, lhs->f64 <= rhs->f64 );
	STR: return VALUE( I64, i64, lhs->str->len <= rhs->str->len );
}

Value EvalGt( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, lhs->i64 > rhs->i64 );
	F64: return VALUE( F64, f64, lhs->f64 > rhs->f64 );
	STR: return VALUE( I64, i64, lhs->str->len > rhs->str->len );
}

Value EvalGe( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, lhs->i64 >= rhs->i64 );
	F64: return VALUE( F64, f64, lhs->f64 >= rhs->f64 );
	STR: return VALUE( I64, i64, lhs->str->len >= rhs->str->len );
}

Value EvalAnd( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, lhs->i64 && rhs->i64 );
	F64: return VALUE( F64, f64, lhs->f64 && rhs->f64 );
	STR: return VALUE( I64, i64, lhs->str && rhs->str );
}

Value EvalOr( Value *lhs, Value *rhs )
{
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, lhs->i64 || rhs->i64 );
	F64: return VALUE( F64, f64, lhs->f64 || rhs->f64 );
	STR: return VALUE( I64, i64, lhs->str || rhs->str );
}

Value EvalMov( Value *lhs, Value *rhs )
{	/* Just return RHS val */
	static Label *ops[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *ops[ lhs->type ];
	I64: return VALUE( I64, i64, rhs->i64 );
	F64: return VALUE( F64, f64, rhs->f64 );
	STR: return VALUE( STR, str, rhs->str );
}

Value EvalAddEq( Value *lhs, Value *rhs )
{
	return EvalAdd( lhs, rhs );
}

Value EvalSubEq( Value *lhs, Value *rhs )
{
	return EvalSub( lhs, rhs );
}

Value EvalMulEq( Value *lhs, Value *rhs )
{
	return EvalMul( lhs, rhs );
}

Value EvalDivEq( Value *lhs, Value *rhs )
{
	return EvalDiv( lhs, rhs );
}

Value EvalModEq( Value *lhs, Value *rhs )
{
	return EvalMod( lhs, rhs );
}

Value EvalPowEq( Value *lhs, Value *rhs )
{
	return EvalPow( lhs, rhs );
}

Value EvalBandEq( Value *lhs, Value *rhs )
{
	return EvalBand( lhs, rhs );
}

Value EvalBorEq( Value *lhs, Value *rhs )
{
	return EvalBor( lhs, rhs );
}

Value EvalBxorEq( Value *lhs, Value *rhs )
{
	return EvalBxor( lhs, rhs );
}

Value EvalLshEq( Value *lhs, Value *rhs )
{
	return EvalLsh( lhs, rhs );
}

Value EvalRshEq( Value *lhs, Value *rhs )
{
	return EvalRsh( lhs, rhs );
}