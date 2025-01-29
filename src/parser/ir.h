#define X_IR_ENUM( ENUM ) ENUM,
/* Generates label pointers in: compiler/unary/unary.c */
#define X_UNAIR_LBL1( ENUM ) &&unary_##ENUM,
#define X_UNAIR_FN1( ENUM ) unary_##ENUM: return unary_##ENUM( c, oc, rhs );
/* Generates label pointers in: compiler/binary/binary.c */
#define X_BINIR_LBL2( ENUM ) &&binary_##ENUM,
#define X_BINIR_LBL1( ENUM ) CMP_IRS2( ENUM##_, X_BINIR_LBL2 )
/* Generates labels and calls for: compiler/binary/binary.c */
#define X_BINIR_FN2( ENUM ) binary_##ENUM: return binary_##ENUM( c, lhs, oc, rhs );
#define X_BINIR_FN1( ENUM ) CMP_IRS2( ENUM##_, X_BINIR_FN2 )

#define NCMP_IRS( V, X ) /* Non-compilable */\
	X( V##none )\
	X( V##fn )\
	X( V##arg )

#define IR_CMP_BASE ir_const /* start of compilable IRs */
#define IR_CMP_N ( ir_n - IR_CMP_BASE ) /* N compilable IRs */

#define CMP_IRS( V, X ) /* Compilable */\
	X( V##const )\
	X( V##ref )\
	X( V##call )\

#define CMP_IRS2( V, X ) /* For self-iteration */\
	X( V##const )\
	X( V##ref )\
	X( V##call )\

#define IRS( V, X ) /* Expands both ir types */\
	NCMP_IRS( V, X )\
	CMP_IRS( V, X )

enum ir_type
{	/* IRS() only used here for now */
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
