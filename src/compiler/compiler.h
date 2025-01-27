enum opcode
{
	OPCODES( op_, X_OPCODE_ENUM )
	op_n
};

struct op
{
	opcode op;
	u8 r;
	u8 a;
	u8 b;
};

struct compiler
{
	parser* parser;
	vec* consts; /* vec< value > */
	vec* vars; /* vec< var >: function local vars */
	bslog* log;
};

void compiler_init( compiler* compiler, heap* heap, parser* parser );
opcode tk_to_op( token_type tk );
u32 const_push( compiler* compiler, value* value );
value* const_get( compiler* compiler, u32 idx );
u32 var_push( compiler* compiler, str* name, value* value );
var* var_get( compiler* compiler, str* name );
u32 op_push( compiler* compiler, opcode op, u8 r, u8 a, u8 b );
op* op_get( compiler* compiler, u32 idx );