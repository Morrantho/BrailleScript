#define X_BIN_LBL3( OP, ENUM ) &&OP##ENUM,

#define X_BIN_LBL2( OP, ENUM )\
	{ VALUE_TYPES2( OP, ENUM##_, X_BIN_LBL3 ) },

#define X_BIN_LBL( TK, OP )\
	{ VALUE_TYPES( OP##_, , X_BIN_LBL2 ) },

#define BIN_EVAL( T, V )\
	out->value.type = value_##T;\
	out->value.T = V;\
	return;

u8 binary_foldable( ir* lhs, ir* rhs );
void binary_fold( ir* out, ir* l, opcode oc, ir* r );
void binary_compile( compiler* c, parser* p );