#define BIN_EVAL( T, V )\
	out->value.type = value_##T;\
	out->value.T = V;\
	return;

void binary_fold( compiler* c, ir* l, opcode oc, ir* r );
void binary_compile( compiler* c, parser* p );