typedef enum Prec
{
	PREC_NONE,
	PREC_LIST, /* , */
	PREC_BITEQ, /* &=, ^=, |= */ 
	PREC_SHEQ, /* <<=, >>= */
	PREC_TERMEQ, /* +=, -= */
	PREC_FACTEQ, /* *=, /=, %= */
	PREC_POWEQ, /* **= */
	PREC_EQ, /* =, : */
	PREC_TERN, /* ?: */
	PREC_OR, /* || */
	PREC_AND, /* && */
	PREC_BOR, /* | */
	PREC_BXOR, /* ^ */
	PREC_BAND, /* & */
	PREC_EQNEQ, /* ==, != */
	PREC_GTLT, /* >, >=, <, <= */
	PREC_SH, /* <<, >> */
	PREC_TERM, /* +, - */
	PREC_FACT, /* *, /, % */
	PREC_POW, /* ** */
	PREC_NOT, /* !, ~ */
	PREC_PLUSMINUS, /* +, - */
	PREC_PRETERM, /* ++, -- */
	PREC_MEMBER, /* . */
	PREC_INDEX, /* [] */
	PREC_CALL,/* () */
	PREC_POSTTERM, /* ++, -- */
} Prec;