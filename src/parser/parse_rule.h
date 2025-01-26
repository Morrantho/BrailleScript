#ifndef BS_PARSE_RULE_H
#define BS_PARSE_RULE_H

typedef enum prec
{
	PRECS( prec_, X_PREC_ENUM )
	prec_n
} prec;

typedef struct parse_rule
{
	void* nud;
	void* led;
	prec prec;
} parse_rule;

#endif
