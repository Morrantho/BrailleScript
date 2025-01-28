#define UNA_EVAL( T, V )\
	out->value.type = value_##T;\
	out->value.T = V;\
	return;

void unary_fold( compiler* c, opcode oc, ir* rhs );
void unary_compile( compiler* c, parser* p );