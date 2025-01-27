opcode tk_to_op( token_type tk )
{
	static const opcode ops[ tk_n ] = { OPCODES( op_, X_OPCODE_TOKEN ) };
	return ops[ tk ];
}
