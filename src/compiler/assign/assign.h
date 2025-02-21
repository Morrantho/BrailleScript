U32 AssignConst( U32 dest, Var *var )
{
	return PackABX( OP_LOADC, dest, ConstPush( var->value ) );
}

U32 AssignRef( U32 dest, Var *var )
{
	Compiler *compiler = GetCompiler( );
	U32 src;
	Var *ref = LocalGet( &src, compiler->fn, var->value.str );
	if( ref ){ return PackABX( OP_MOV, dest, src ); }
	ref = GlobalGet( &src, var->value.str );
	if( ref ){ return PackABX( OP_LOADG, dest, src ); }
	I8 *val = ArenaOff( GetStrings( ), var->value.str->offset );
	Throw( "Assignment to undefined reference: %s\n", val );
	return 0;
}

U32 AssignCall( U32 dest, Var *var )
{
	return 0;
}

U32 Assign( U32 dest, Var *var, ParseType T )
{
	static Label *types[ ] = { &&CONST, &&REF, &&CALL };
	goto *types[ T ];
	CONST: return AssignConst( dest, var );
	REF: return AssignRef( dest, var );
	CALL: return AssignCall( dest, var );
}

U32 GlobalAssign( U32 dest, Var *var, String *name, ParseNode *rhs )
{
	if( !var ){ var = GlobalPush( &dest, name, rhs->value ); }
	var->value = rhs->value;
	return Assign( dest, var, rhs->type );
}

U32 LocalAssign( Func *fn, String *name, ParseNode *rhs )
{
	U32 dest = 0;
	Var *var = LocalGet( &dest, fn, name );
	if( !var ){ var = LocalPush( &dest, fn, name, rhs->value ); }
	var->value = rhs->value;
	return Assign( dest, var, rhs->type );
}

U32 CompileAssign( String *name, ParseNode *rhs )
{
	Compiler *compiler = GetCompiler( );
	U32 dest = 0;
	Var *var = GlobalGet( &dest, name );
	if( !compiler->fn ){ return GlobalAssign( dest, var, name, rhs ); }
	if( var ){ return GlobalAssign( dest, var, name, rhs ); } /* global assign */
	return LocalAssign( compiler->fn, name, rhs ); /* local assign */
}