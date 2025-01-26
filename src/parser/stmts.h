#ifndef BS_STMTS_H
#define BS_STMTS_H

#define X_STMT_LBL( TK, LBL ) [ TK ] = &&LBL,

/* Only statements that can derive a start symbol. */
#define STMTS( X )\
	X( 0 ... tk_n - 1, EXPR )\
	X( tk_ret, RET )\
	X( tk_if, IF )\
	X( tk_for, FOR )\
	X( tk_fn, FN )\
	X( tk_while, WHILE )\
	X( tk_do, DO )\
	X( tk_id, ASSIGN )

#endif