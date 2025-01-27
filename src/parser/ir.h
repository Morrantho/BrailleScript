enum ir_type
{
	ir_none, /* used to track when to stop popping irs of some kind */
	ir_const,
	ir_ref,
	ir_call,
	ir_binop,
	ir_unop,
	ir_fn,
	ir_arg,
	ir_n
};

struct ir
{
	ir_type ir_type;
	value_type value_type;
	union
	{
		i64 i64;
		f64 f64;
		str* str;
		// opcode opcode;
	};
};

void ir_logeval( ir* evald );
ir* ir_push( parser* parser, ir_type it, value_type vt, void* value );
