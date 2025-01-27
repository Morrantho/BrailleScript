struct parse_rule
{
	void* nud;
	void* led;
	prec prec;
};

#define X_EXPR_RULE( ENUM, NUD, LED, PREC )\
	[ ENUM ] = { .nud = &&NUD, .led = &&LED, .prec = PREC },

#define EXPRS( X )\
	X( tk_eof, EOS, EOS, prec_none )\
	\
	X( tk_add, UNARY, BINARY, prec_term )\
	X( tk_addeq, ERR, BINARY, prec_term_eq )\
	X( tk_addadd, UNARY, ERR, prec_postterm )\
	\
	X( tk_sub, UNARY, BINARY, prec_term )\
	X( tk_subeq, ERR, BINARY, prec_term_eq )\
	X( tk_subsub, UNARY, ERR, prec_postterm )\
	\
	X( tk_mul, ERR, BINARY, prec_fact )\
	X( tk_muleq, ERR, BINARY, prec_fact_eq )\
	X( tk_pow, ERR, BINARY, prec_not ) /* pow might need its own prec*/\
	\
	X( tk_div, ERR, BINARY, prec_fact )\
	X( tk_diveq, ERR, BINARY, prec_fact_eq )\
	\
	X( tk_mod, ERR, BINARY, prec_fact )\
	X( tk_modeq, ERR, BINARY, prec_and_eq )\
	\
	X( tk_band,	ERR, BINARY, prec_band )\
	X( tk_bandeq, ERR, BINARY, prec_and_eq )\
	X( tk_and, ERR, BINARY, prec_and )\
	\
	X( tk_bor, ERR, BINARY, prec_bor )\
	X( tk_boreq, ERR, BINARY, prec_or_eq )\
	X( tk_or, ERR, BINARY, prec_or )\
	\
	X( tk_bxor,	ERR, BINARY, prec_bxor )\
	X( tk_bxoreq, ERR, BINARY, prec_or_eq )\
	\
	X( tk_lt, ERR, BINARY, prec_gt_lt )\
	X( tk_le, ERR, BINARY, prec_gt_lt )\
	X( tk_lsh, ERR, BINARY, prec_sh )\
	X( tk_lsheq, ERR, BINARY, prec_sh_eq )\
	\
	X( tk_gt, ERR, BINARY, prec_gt_lt )\
	X( tk_ge, ERR, BINARY, prec_gt_lt )\
	X( tk_rsh, ERR, BINARY, prec_sh )\
	X( tk_rsheq, ERR, BINARY, prec_sh_eq )\
	\
	X( tk_eq, ERR, ERR, prec_eq )\
	X( tk_eqeq,	ERR, BINARY, prec_eq_neq )\
	\
	X( tk_not, UNARY, ERR, prec_not )\
	X( tk_neq, ERR, BINARY, prec_eq_neq )\
	\
	X( tk_bnot,	UNARY, ERR, prec_not )\
	X( tk_len, ERR, ERR, prec_gt_lt ) /* tweak me */\
	X( tk_ret, ERR, ERR, prec_member ) /* tweak me */\
	\
	X( tk_lp, GROUP, ERR, prec_call )\
	X( tk_rp, ERR, ERR, prec_call )\
	X( tk_ls, ERR, ERR, prec_index )\
	X( tk_rs, ERR, ERR, prec_index )\
	X( tk_lc, ERR, ERR, prec_none )\
	X( tk_rc, ERR, ERR, prec_none )\
	\
	X( tk_dot, ERR, ERR, prec_member )\
	X( tk_else, ERR, ERR, prec_none )\
	X( tk_if, ERR, ERR, prec_none )\
	X( tk_for, ERR, ERR, prec_none )\
	\
	X( tk_col, ERR, ERR, prec_eq )\
	X( tk_end, ERR, ERR, prec_none )\
	X( tk_then,	ERR, ERR, prec_none )\
	\
	X( tk_semi,	ERR, ERR, prec_none )\
	X( tk_while, ERR, ERR, prec_none )\
	X( tk_do, ERR, ERR, prec_none )\
	\
	X( tk_com, ERR, ERR, prec_list )\
	\
	X( tk_i64, I64, ERR, prec_none )\
	X( tk_f64, F64, ERR, prec_none )\
	X( tk_str, STR, ERR, prec_none )\
	X( tk_id, REF, ERR, prec_none )
