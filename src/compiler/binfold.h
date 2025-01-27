#define X_BIN_LBL3( OP, ENUM ) &&OP##ENUM,

#define X_BIN_LBL2( OP, ENUM )\
	{ VALUE_TYPES2( OP, ENUM##_, X_BIN_LBL3 ) },

#define X_BIN_LBL( TK, OP )\
	{ VALUE_TYPES( OP##_, , X_BIN_LBL2 ) },

#define BIN_EVAL( T, V ) out->value_type = value_##T; out->T = V; return;

u8 bin_foldable( ir* lhs, ir* rhs );
void bin_fold( ir* out, ir* l, ir* op, ir* r );
