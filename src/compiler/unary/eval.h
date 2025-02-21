Value EvalUnaErr( OpCode op, Value *rhs )
{
	Throw( "Illegal Unary Operation: %d\n", op );
	return ( Value ){ 0 };
}

Value EvalNot( Value *rhs )
{
	static Label *types[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *types[ rhs->type ];
	I64: return VALUE( I64, i64, !rhs->i64 );
	F64: return VALUE( F64, f64, !rhs->f64 );
	STR: return VALUE( STR, str, rhs->str );
}

Value EvalBnot( Value *rhs )
{
	static Label *types[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *types[ rhs->type ];
	I64: return VALUE( I64, i64, ~rhs->i64 );
	F64: return VALUE( F64, f64, ~( I64 )rhs->f64 );
	STR: return VALUE( STR, str, rhs->str );
}

Value EvalPlus( Value *rhs )
{
	static Label *types[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *types[ rhs->type ];
	I64: return VALUE( I64, i64, +rhs->i64 );
	F64: return VALUE( F64, f64, +rhs->f64 );
	STR: return VALUE( STR, str, rhs->str );
}

Value EvalMinus( Value *rhs )
{
	static Label *types[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *types[ rhs->type ];
	I64: return VALUE( I64, i64, -rhs->i64 );
	F64: return VALUE( F64, f64, -rhs->f64 );
	STR: return VALUE( STR, str, rhs->str );
}

Value EvalInc( Value *rhs )
{
	static Label *types[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *types[ rhs->type ];
	I64: return VALUE( I64, i64, rhs->i64 + 1 );
	F64: return VALUE( F64, f64, rhs->f64 + 1 );
	STR: return VALUE( STR, str, rhs->str );
}

Value EvalDec( Value *rhs )
{
	static Label *types[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *types[ rhs->type ];
	I64: return VALUE( I64, i64, rhs->i64 - 1 );
	F64: return VALUE( F64, f64, rhs->f64 - 1 );
	STR: return VALUE( STR, str, rhs->str );
}