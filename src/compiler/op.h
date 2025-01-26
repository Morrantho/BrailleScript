#ifndef BS_OP_H
#define BS_OP_H

typedef enum opcode
{
	OPCODES( op_, X_OPCODE_ENUM )
	op_n
} opcode;

typedef struct op
{
	opcode op;
	u8 r;
	u8 a;
	u8 b;
} op;

stil opcode tk_to_op( token_type tk )
{
	static const opcode ops[ tk_n ] = { OPCODES( op_, X_OPCODE_TOKEN ) };
	return ops[ tk ];
}

#endif