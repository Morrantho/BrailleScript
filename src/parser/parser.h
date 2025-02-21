typedef struct ParseNode
{
	ParseType type;
	Value value;
} ParseNode;

typedef struct ParseRule
{
	Label *nud;
	Label *led;
	Prec prec;
} ParseRule;

typedef struct Parser
{
	Token token;
} Parser;

Parser *GetParser( )
{
	static Parser parser = { 0 };
	return &parser;
}

ParseNode ParseExpr( Parser *parser, Prec prec );
ParseNode ParseStmt( Parser *parser );
ParseNode CompileBin( ParseNode *lhs, TokenType op, ParseNode *rhs );
ParseNode CompileUna( TokenType type, ParseNode *rhs );
U32 CompileAssign( String *name, ParseNode *rhs );

Void ParserInit( )
{
	// Parser *parser = GetParser( );
	// parser->token = Lex( );
}

void ParseNodeLog( ParseNode* node )
{
	static Label *types[ VALUE_N ] = { &&I64, &&F64, &&STR };
	if( node->type != PT_CONST ){ return; }
	goto *types[ node->value.type ];
	I64:
		printf( "%ld\n", node->value.i64 );
		return;
	F64:
		printf( "%f\n", node->value.f64 );
		return;
	STR:
		Arena *strings = GetStrings( );
		I8 *cstr = ArenaOff( strings, node->value.str->offset );
		printf( "%s\n", cstr );
		return;
}

Void ParseMatch( Parser *parser, TokenType type )
{
	if( type != parser->token.type )
	{
		Throw( "Expected: %d Got: %d\n", type, parser->token.type );
	}
	parser->token = Lex( );
}
/*******************************************************************************/
/* Statements */
/*******************************************************************************/
ParseNode ParseIf( Parser *parser )
{
	ParseMatch( parser, TK_IF );
	ParseNode cond = ParseExpr( parser, PREC_NONE );
	/* emit conditional */
	ParseMatch( parser, TK_THEN );
	/* emit jmp then backpatch */
	for( ; parser->token.type; )
	{
		ParseNode stmt = ParseStmt( parser );
		if( parser->token.type == TK_END ){ break; }
		if( parser->token.type == TK_ELSE )
		{
			ParseMatch( parser, TK_ELSE );
			/* emit else then backpatch */
		}
	}
	ParseMatch( parser, TK_END );
	return ( ParseNode ){ 0 };
}

ParseNode ParseFor( Parser *parser )
{
	ParseMatch( parser, TK_FOR );
	return ( ParseNode ){ 0 };	
}

ParseNode ParseDo( Parser *parser )
{
	ParseMatch( parser, TK_DO );
	return ( ParseNode ){ 0 };	
}

ParseNode ParseWhile( Parser *parser )
{
	ParseMatch( parser, TK_WHILE );
	return ( ParseNode ){ 0 };	
}

ParseNode ParseFunc( Parser *parser, String *name )
{
	ParseMatch( parser, TK_LP );
	/* ParseArgs( ); */
	ParseMatch( parser, TK_RP );
	while( parser->token.type && parser->token.type != TK_END )
	{
		ParseStmt( parser );
	}
	ParseMatch( parser, TK_END );
	return ( ParseNode ){ 0 };
}

ParseNode ParseId( Parser *parser )
{
	String* name = parser->token.value.str;
	ParseMatch( parser, TK_ID );
	ParseMatch( parser, TK_COLON );
	if( parser->token.type == TK_LP ){ return ParseFunc( parser, name ); }
	ParseNode rhs = ParseExpr( parser, PREC_NONE );
	CompileAssign( name, &rhs );
	return rhs;
}
/*******************************************************************************/
/* Expressions */
/*******************************************************************************/
ParseNode ParseEos( Parser *parser )
{
	return ( ParseNode ){ 0 };
}

ParseNode ParseErr( Parser *parser )
{
	Throw( "Illegal operation: %d\n", parser->token.type );
	return ( ParseNode ){ 0 };
}

ParseNode ParseUnary( Parser *parser, Prec cur )
{
	TokenType op = parser->token.type;
	ParseMatch( parser, parser->token.type ); /* op */
	ParseNode rhs = ParseExpr( parser, cur );
	return CompileUna( op, &rhs );
}

ParseNode ParseBinary( Parser *parser, ParseNode *lhs, Prec cur )
{
	TokenType op = parser->token.type;
	ParseMatch( parser, parser->token.type ); /* op */
	ParseNode rhs = ParseExpr( parser, cur );
	return CompileBin( lhs, op, &rhs );
}

ParseNode ParseGroup( Parser *parser )
{
	ParseMatch( parser, TK_LP );
	ParseNode node = ParseExpr( parser, PREC_NONE );
	ParseMatch( parser, TK_RP );
	return node;
}

ParseNode ParseCall( Parser *parser )
{
	String* name = parser->token.value.str;
	ParseMatch( parser, TK_ID );
	ParseMatch( parser, TK_LP );
	/* ParseArgs( ) */
	ParseMatch( parser, TK_RP );
	return ( ParseNode ){ 0 };
}

ParseNode ParseI64( Parser *parser )
{
	ParseNode node = { .type = PT_CONST, .value.type = VALUE_I64 };
	node.value.i64 = parser->token.value.i64;
	ParseMatch( parser, TK_I64 );
	return node;
}

ParseNode ParseF64( Parser *parser )
{
	ParseNode node = { .type = PT_CONST, .value.type = VALUE_F64 };
	node.value.f64 = parser->token.value.f64;
	ParseMatch( parser, TK_F64 );
	return node;
}

ParseNode ParseStr( Parser *parser )
{
	ParseNode node = { .type = PT_CONST, .value.type = VALUE_STR };
	node.value.str = parser->token.value.str;
	ParseMatch( parser, TK_STR );
	return node;
}

ParseNode ParseRef( Parser *parser )
{
	ParseNode node = { .type = PT_REF, .value.type = VALUE_STR };
	node.value.str = parser->token.value.str;
	ParseMatch( parser, TK_ID );
	return node;
}

ParseNode ParseExpr( Parser *parser, Prec prec )
{
	#include "expr_table.h"
	ParseRule *rule = &rules[ parser->token.type ];
	ParseNode node = { 0 };
	goto *rule->nud;
	LED:
		rule = &rules[ parser->token.type ];
		if( rule->prec > prec ){ goto *rule->led; }
		goto DONE;
	#include "expr_labels.h"
	DONE: return node;
}

ParseNode ParseStmt( Parser *parser )
{
	#include "stmt_table.h"
	goto *stmts[ parser->token.type ];
	#include "stmt_labels.h"
}

Void Parse( )
{
	Parser *parser = GetParser( );
	parser->token = Lex( );
	while( parser->token.type != TK_EOS )
	{
		ParseStmt( parser );
	}
}