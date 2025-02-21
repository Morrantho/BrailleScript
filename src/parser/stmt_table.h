static Label *stmts[ ] =
{
	[ 0 ... TK_N - 1 ] = &&EXPR,
	[ TK_IF ] = &&IF,
	[ TK_FOR ] = &&FOR,
	[ TK_DO ] = &&DO,
	[ TK_WHILE ] = &&WHILE,
	[ TK_ID ] = &&ID
};