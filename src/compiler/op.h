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

opcode tk_to_op( token_type tk );
