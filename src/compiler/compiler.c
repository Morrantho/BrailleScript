void compiler_init( compiler* compiler, heap* heap, parser* parser )
{
	compiler->parser = parser;
	compiler->consts = &heap->consts;
	compiler->vars = &heap->vars;
	compiler->log = parser->log;
}

opcode tk_to_op( token_type tk )
{	/* FIX ME */
	// static const opcode ops[ tk_n ] = { OPCODES( op_, X_OPCODE_TOKEN ) };
	// return ops[ tk ];
	return 0;
}

u32 const_push( compiler* compiler, value* value )
{
	return vec_push( compiler->consts, value );
}

value* const_get( compiler* compiler, u32 idx )
{
	return ( value* )vec_get( compiler->consts, idx );
}

u32 var_push( compiler* compiler, str* name, value* value )
{
	var var = { .name = name, .value = value };
	var.idx = compiler->vars->len;
	/* TODO: ++ cur fn nvars */
	return vec_push( compiler->vars, &var );
}

var* var_get( compiler* compiler, str* name )
{	/* TODO: Only look at the current functions nvars */
	u32 nvars = compiler->vars->len - 1;
	for( i32 i = nvars; i >= 0; i-- )
	{
		var* var = vec_get( compiler->vars, i );
		if( var->name == name ){ return var; }
	}
	return NULL;
}

u32 op_push( compiler* compiler, opcode oc, u8 r, u8 a, u8 b )
{
	// op op = { .op = oc, .r = r, .a = a, .b = b };
	// return vec_push( compiler->ops, &op );
	return 0;
}

op* op_get( compiler* compiler, u32 idx )
{
	// return vec_get( compiler->ops, idx );
	return 0;
}