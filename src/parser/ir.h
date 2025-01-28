#define X_IR_ENUM( ENUM ) ENUM,

#define X_UNAIR_LBL1( ENUM ) &&unary_##ENUM,
#define X_UNAIR_FN1( ENUM ) unary_##ENUM: return unary_##ENUM( c, oc, rhs );

#define X_BINIR_LBL2( ENUM ) &&binary_##ENUM,
#define X_BINIR_LBL1( ENUM ) IRS2( ENUM##_, X_BINIR_LBL2 )
#define X_BINIR_FN2( ENUM ) binary_##ENUM: return binary_##ENUM( c, lhs, oc, rhs );
#define X_BINIR_FN1( ENUM ) IRS2( ENUM##_, X_BINIR_FN2 )

#define IRS( V, X )\
	X( V##none ) /* used as a stopping point */\
	X( V##const )\
	X( V##ref ) /* variable reference / name */\
	X( V##call )\
	X( V##fn ) /* function def, not a call */\
	X( V##arg )

#define IRS2( V, X )\
	X( V##none )\
	X( V##const )\
	X( V##ref )\
	X( V##call )\
	X( V##fn )\
	X( V##arg )

enum ir_type
{
	IRS( ir_, X_IR_ENUM )
	ir_n
};

struct ir
{
	ir_type type; /* 4 */
	u32 idx; /* const idx, local idx, fn idx, etc */
	value value; /* 12 */
	// var* var;
};

void ir_logeval( ir* evald );
ir* ir_push( parser* parser, ir_type it, value_type vt, void* value );
