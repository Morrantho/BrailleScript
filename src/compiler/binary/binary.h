ValueType BinPromote( ParseNode *lhs, ParseNode *rhs )
{
	#include "promote_table.h"
	return types[ lhs->value.type ][ rhs->value.type ];
}

Void BinCast( ParseNode *node, ValueType common )
{
	#include "cast_table.h"
	node->value.type = common;
	goto *types[ node->value.type ][ common ];
	#include "cast_labels.h"
}

Value BinFold( ParseNode *lhs, OpCode op, ParseNode *rhs )
{
	#include "fold_table.h"
	goto *ops[ op ];
	#include "fold_labels.h"
}

ParseNode BinConstConst( ParseNode *lhs, OpCode op, ParseNode *rhs )
{
	ParseNode node = { .type = PT_CONST, .value.type = lhs->value.type };
	node.value = BinFold( lhs, op, rhs );
	return node;
}

ParseNode BinConstRef( ParseNode *lhs, OpCode op, ParseNode *rhs )
{
	return ( ParseNode ){ 0 };
}

ParseNode BinConstCall( ParseNode *lhs, OpCode op, ParseNode *rhs )
{
	return ( ParseNode ){ 0 };
}

ParseNode BinRefConst( ParseNode *lhs, OpCode op, ParseNode *rhs )
{
	return ( ParseNode ){ 0 };
}

ParseNode BinRefRef( ParseNode *lhs, OpCode op, ParseNode *rhs )
{
	return ( ParseNode ){ 0 };
}

ParseNode BinRefCall( ParseNode *lhs, OpCode op, ParseNode *rhs )
{
	return ( ParseNode ){ 0 };
}

ParseNode BinCallConst( ParseNode *lhs, OpCode op, ParseNode *rhs )
{
	return ( ParseNode ){ 0 };
}

ParseNode BinCallRef( ParseNode *lhs, OpCode op, ParseNode *rhs )
{
	return ( ParseNode ){ 0 };
}

ParseNode BinCallCall( ParseNode *lhs, OpCode op, ParseNode *rhs )
{
	return ( ParseNode ){ 0 };
}

ParseNode CompileBin( ParseNode *lhs, TokenType token_type, ParseNode *rhs )
{
	#include "ir_table.h"
	OpCode op = TkToOp( token_type );
	ValueType common = BinPromote( lhs, rhs );
	BinCast( lhs, common );
	BinCast( rhs, common );
	goto *irs[ lhs->type ][ rhs->type ];
	#include "ir_labels.h"
}