void compiler_init( compiler* compiler, heap* heap, parser* parser )
{
	compiler->parser = parser;
	compiler->consts = &heap->consts;
	compiler->vars = &heap->vars;
	compiler->ops = &heap->ops;
	compiler->funcs = &heap->funcs;
	compiler->log = parser->log;
	func_commit( compiler );
}
/* Yields a base opcode for binary and unary operators. Base opcodes all
** start from the first existing value_type, e.g. value_i64
*/
i64 tk_to_op( token_type tk )
{	/* FIX: op_add_i64, op_plus_i64, op_sub_i64, op_minus_i64 */
	static const opcode ops[ tk_n ] = { OPCODES( op_, X_OP_MAP ) };
	return ops[ tk ];
}

u32 const_push( compiler* compiler, value* value )
{
	compiler->func->nconsts++;
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
	compiler->func->nvars++;
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
	op* op = vec_commit( compiler->ops );
	op->dest = r;
	op->src1 = a;
	op->src2 = b;
	compiler->func->nops++;
	return compiler->ops->len - 1;
}

op* op_get( compiler* compiler, u32 idx )
{
	return vec_get( compiler->ops, idx );
}

void func_commit( compiler* c )
{
	func* fn = vec_commit( c->funcs );
	fn->iconsts = c->consts->len;
	fn->ivars = c->vars->len;
	fn->iops = c->consts->len;
	fn->nconsts = 0;
	fn->nvars = 0;
	fn->nops = 0;
	fn->nargs = 0;

	c->func = fn; /* update current fn */
}