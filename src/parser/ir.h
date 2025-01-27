#define X_IRS_ENUM( ENUM, LBL ) ENUM,
#define X_IRS_LBL( ENUM, LBL ) [ ENUM ] = &&LBL,

#define IRS( V, X )\
	X( V##none, ERR ) /* used as a marker / stopping point */\
	X( V##const, CONST )\
	X( V##ref, REF )\
	X( V##call, CALL )\
	X( V##binop, ERR )\
	X( V##unop, ERR )\
	X( V##fn, ERR )\
	X( V##arg, ERR )

enum ir_type
{
	IRS( ir_, X_IRS_ENUM )
	ir_n
};

struct ir
{
	ir_type ir_type; /* 4 */
	u32 idx; /* const idx, local idx, fn idx, etc */
	value value; /* 12 */
	// var* var;
};

void ir_logeval( ir* evald );
ir* ir_push( parser* parser, ir_type it, value_type vt, void* value );
