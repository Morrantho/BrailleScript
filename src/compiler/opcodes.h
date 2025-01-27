#define X_OPCODE_ENUM( TK, ENUM ) ENUM,
#define X_OPCODE_TOKEN( TK, ENUM ) [ tk_##TK ] = ENUM,
#define X_OPCODE_LBL( TK, ENUM ) [ ENUM ] = &&ENUM,

#define OP_UNA( V, X )\
	X( not, V##not )\
	X( bnot, V##bnot )\
	X( len, V##len )\
	X( ret, V##ret )
#define OP_UNA2( V, X ) /* expanded in unafold.h */\
	X( add, V##plus ) /* these are laid out specifically to let us */\
	X( sub, V##neg ) /* share unary + and - with binary + and - */
#define OP_BIN( V, X )\
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

// X( eof, V##nop )
#define OPCODES( V, X )\
	OP_UNA( V, X )\
	OP_BIN( V, X )
