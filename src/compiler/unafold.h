#define X_UNA_LBL2( OP, ENUM ) &&OP##ENUM,

#define X_UNA_LBL( TK, OP )\
	{ VALUE_TYPES( OP##_, , X_UNA_LBL2 ) },

#define UNA_EVAL( T, V ) out->value_type = value_##T; out->T = V; return;

u8 una_foldable( ir* op );
void una_fold( ir* out, ir* op, ir* r );
