typedef enum TokenType
{
	TK_EOS,

	TK_NOT,
	TK_NEQ,

	TK_BNOT,

	TK_ADD,
	TK_ADDEQ,
	TK_ADDADD,

	TK_SUB,
	TK_SUBEQ,
	TK_SUBSUB,

	TK_MUL,
	TK_MULEQ,
	TK_POW,
	TK_POWEQ,

	TK_DIV,
	TK_DIVEQ,

	TK_MOD,
	TK_MODEQ,

	TK_BAND,
	TK_BANDEQ,
	TK_AND,

	TK_BOR,
	TK_BOREQ,
	TK_OR,

	TK_BXOR,
	TK_BXOREQ,

	TK_EQ,
	TK_EQEQ,

	TK_LT,
	TK_LE,
	TK_LSH,
	TK_LSHEQ,

	TK_GT,
	TK_GE,
	TK_RSH,
	TK_RSHEQ,

	TK_LP,
	TK_RP,
	TK_LS,
	TK_RS,
	TK_LC,
	TK_RC,

	TK_DOT, /* . */
	TK_IF, /* .: */
	TK_FOR, /* .; */
	TK_ELSE, /* .. */

	TK_SEMI, /* ; */
	TK_DO, /* ;. */
	TK_WHILE, /* ;; */

	TK_COLON, /* : :. :: */
	TK_THEN, /* :. */
	TK_END, /* :: */

	TK_COMMA, /* , */
	TK_RET, /* @ */

	TK_I64,
	TK_F64,
	TK_STR,
	TK_ID,

	TK_N
} TokenType;