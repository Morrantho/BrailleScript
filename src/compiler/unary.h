#define X_UNA_LBL2( OP, ENUM ) &&OP##ENUM,

#define X_UNA_LBL( TK, OP )\
	{ VALUE_TYPES( OP##_, , X_UNA_LBL2 ) },

#define UNA_EVAL( T, V )\
	out->value.type = value_##T;\
	out->value.T = V;\
	return;

u8 unary_foldable( ir* op );
void unary_fold( ir* out, opcode oc, ir* r );
void unary_compile( compiler* c, parser* p );