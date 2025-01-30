void func_next( compiler* c )
{
	func* fn = vec_commit( c->funcs );
	fn->iconsts = c->consts->len;
	fn->ivars = c->vars->len;
	fn->iops = c->consts->len;
	fn->nconsts = 0;
	fn->nvars = 0;
	fn->nops = 0;
	fn->nargs = 0;
}