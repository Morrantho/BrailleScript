#define EVAL( T, V )\
	out->value.T = V;\
	return;

struct func
{	/* sizeof( 40 ) */
	str* name;
	// u32 iargs; /* start args */
	u32 nargs; /* len args */
	u32 iconsts; /* start of consts */
	u32 nconsts; /* len consts */
	u32 ivars; /* start of vars */
	u32 nvars; /* len vars */
	u32 iops; /* start of ops */
	u32 nops; /* len ops */
};

struct compiler
{
	parser* parser;
	vec* consts; /* vec< value > */
	vec* vars; /* vec< var >: function local vars */
	vec* ops; /* vec< op >: bytecode */
	vec* funcs; /* vec< func > function metadata */
	func* func; /* current compiling function */
	bslog* log;
};

void compiler_init( compiler* compiler, heap* heap, parser* parser );
i64 tk_to_op( token_type tk ); /* returns a base opcode, not a real one */
u32 const_push( compiler* compiler, value* value );
value* const_get( compiler* compiler, u32 idx );
u32 var_push( compiler* compiler, str* name, value* value );
var* var_get( compiler* compiler, str* name );
u32 op_push( compiler* compiler, opcode op, u8 r, u8 a, u8 b );
op* op_get( compiler* compiler, u32 idx );
void func_commit( compiler* c );