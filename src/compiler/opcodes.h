#define UNOPS_BASE op_not_i64
#define BINOPS_BASE op_add_i64

/* All base opcodes start at the first defined value_type: i64 */
#define X_OP_MAP( TK, ENUM ) [ tk_##TK ] = ENUM##_i64,

#define X_OP_VALUE2( ENUM ) ENUM,
#define X_OP_VALUE( TK, ENUM ) VALUE_TYPES( ENUM##_, , X_OP_VALUE2 )

#define UNOPS( V, X )\
	X( not, V##not )\
	X( bnot, V##bnot )\
	X( len, V##len )\
	X( ret, V##ret )

#define UNOPS2( V, X )\
	X( add, V##plus )\
	X( sub, V##minus )

#define BINOPS( V, X )\
	X( add, V##add )\
	X( sub, V##sub )\
	X( mul, V##mul )\
	X( div, V##div )\
	X( mod, V##mod )\
	X( pow, V##pow )\
	X( band, V##band )\
	X( bor, V##bor)\
	X( bxor, V##bxor )\
	X( lsh, V##lsh )\
	X( rsh, V##rsh )\
	X( eqeq, V##eqeq )\
	X( neq, V##neq )\
	X( lt, V##lt )\
	X( le, V##le )\
	X( gt, V##gt )\
	X( ge, V##ge )\
	X( and, V##and )\
	X( or, V##or )\
	X( addeq, V##addeq )\
	X( subeq, V##subeq )\
	X( muleq, V##muleq )\
	X( diveq, V##diveq )\
	X( modeq, V##modeq )\
	X( bandeq, V##bandeq )\
	X( boreq, V##boreq)\
	X( bxoreq, V##bxoreq )\
	X( lsheq, V##lsheq )\
	X( rsheq, V##rsheq )

#define OPCODES( V, X )\
	UNOPS( V, X )\
	UNOPS2( V, X )\
	BINOPS( V, X )

enum opcode
{
	OPCODES( op_, X_OP_VALUE )
	op_n
};

struct op
{
	opcode op;
	u8 dest;
	u8 src1;
	u8 src2;
};