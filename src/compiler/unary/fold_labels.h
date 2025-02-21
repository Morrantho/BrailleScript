ERR: return EvalUnaErr( op, &rhs->value );
NOT: return EvalNot( &rhs->value );
BNOT: return EvalBnot( &rhs->value );
PLUS: return EvalPlus( &rhs->value );
MINUS: return EvalMinus( &rhs->value );
INC: return EvalInc( &rhs->value );
DEC: return EvalDec( &rhs->value );