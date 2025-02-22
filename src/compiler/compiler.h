typedef struct Func
{
	// String *name;
	U32 iconsts;
	U32 ilocals;
	U32 icode;
	// U32 iargs;
	U8 nconsts;
	U8 nlocals;
	U16 ncode;
	// U32 nargs;
} Func;

typedef struct Compiler
{
	Func *fn; /* current compiling function */
	U8 in_fn;
} Compiler;

Compiler *GetCompiler( )
{
	static Compiler compiler = { 0 };
	return &compiler;
}

Void FnCommit( )
{
	Compiler *compiler = GetCompiler( );
	Func *fn = VecCommit( GetFuncs( ) );
	fn->iconsts = GetConsts( )->len;
	fn->ilocals = GetLocals( )->len;
	fn->icode = GetCode( )->len;
	fn->nconsts = fn->nlocals = fn->ncode = 0;
	compiler->fn = fn;
}

U32 ConstPush( Value value )
{ /* 26 bit idx returned */
	Compiler *compiler = GetCompiler( );
	if( compiler->fn ){ compiler->fn->nconsts++; }
	return VecPush( GetConsts( ), &value );
}

Value *ConstGet( U32 idx )
{ /* 26 bit idx */
	return VecGet( GetConsts( ), idx );
}

Var *LocalPush( U8 *dest_reg, Func *fn, String *name, Value value )
{
	if( !fn ){ return NULL; }
	fn->nlocals++;
	Vec *locals = GetLocals( );
	Var *var = VecCommit( locals );
	var->name = name;
	var->value = value;
	*dest_reg = locals->len - 1;
	return var;
}

Var *LocalGet( U8 *dest_reg, Func *fn, String *name )
{
	if( !fn ){ return NULL; }
	Vec *locals = GetLocals( );
	U32 start = fn->ilocals;
	U32 end = ( start + fn->nlocals ) - 1;
	for( ; end >= start; end-- )
	{
		Var *var = VecGet( locals, end );
		if( var->name->offset == name->offset ){ *dest_reg = end; return var; }
	}
	return NULL;
}

Var *GlobalPush( U8 *dest_reg, String *name, Value value )
{
	Vec *globals = GetGlobals( );
	U32 idx = globals->len; /* 26 bit max */
	Var *var = VecCommit( globals );
	var->name = name;
	var->value = value;
	EnvPut( GetEnv( ), name, idx );
	*dest_reg = idx;
	return var;
}

Var *GlobalGet( U8 *dest_reg, String *name )
{
	Evar *evar = EnvGet( GetEnv( ), name );
	if( !evar->idx ){ return NULL; }
	*dest_reg = evar->idx; /* 26 bit global index */
	return EvarToVar( evar );
}

OpCode TkToOp( TokenType type )
{
	#include "token_op_table.h"
	return token_ops[ type ];
}

Void CompilerInit( )
{ /* Reserve globals[ 0 ] for EnvGet() idx comparisons */
	Var *base = VecCommit( GetGlobals( ) );
}