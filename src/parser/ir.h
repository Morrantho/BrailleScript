#ifndef BS_IR_H
#define BS_IR_H

typedef enum ir_type
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
} ir_type;

typedef struct ir
{
	ir_type ir_type;
	value_type value_type;
	union
	{
		i64 i64;
		f64 f64;
		str* str;
		opcode opcode;
	};
} ir;

void ir_logeval( ir* evald )
{
	if( evald->ir_type == ir_none ){ return; }
	switch( evald->value_type )
	{
		case value_i64:
			printf( "%ld\n", evald->i64 ); break;
		case value_f64:
			printf( "%f\n", evald->f64 ); break;
		case value_str:
			printf( "%s\n", ( u8* )( evald->str + 1 ) );
			break;
		default: break;
	}
	evald->ir_type = ir_none;	
}

#endif // BS_IR_H