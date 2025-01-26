#ifndef BS_PREC_H
#define BS_PREC_H

#define X_PREC_ENUM( ENUM ) ENUM,

#define PRECS( V, X )\
	X( V##none )\
	X( V##list ) /* , */\
	X( V##sh_eq ) /* <<=, >>= */\
	X( V##or_eq ) /* ^=, |= */ \
	X( V##and_eq ) /* %=, &= */\
	X( V##fact_eq ) /* *=, /= */\
	X( V##term_eq ) /* +=, -= */\
	X( V##eq ) /* = */\
	X( V##tern ) /* ?: */\
	X( V##or ) /* || */\
	X( V##and ) /* && */\
	X( V##bor ) /* | */\
	X( V##bxor ) /* ^ */\
	X( V##band ) /* & */\
	X( V##eq_neq ) /* ==, != */\
	X( V##gt_lt ) /* >, >=, <, <= */\
	X( V##sh ) /* <<, >> */\
	X( V##term ) /* +, - */\
	X( V##fact ) /* *, /, % */\
	X( V##not ) /* !, ~ */\
	X( V##un ) /* +, - */\
	X( V##preterm ) /* ++, -- */\
	X( V##postterm ) /* ++, -- */\
	X( V##member ) /* . */\
	X( V##index ) /* [] */\
	X( V##call )/* () */

#endif
