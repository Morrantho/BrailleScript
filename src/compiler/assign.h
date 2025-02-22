U32 AssignConst( U8 dest_reg, Var *var )
{
	return PackABX( OP_LOADC, dest_reg, ConstPush( var->value ) );
}

U32 AssignRef( U8 dest_reg, Var *var )
{
	Compiler *compiler = GetCompiler( );
	U8 src_reg;
	Var *ref = LocalGet( &src_reg, compiler->fn, var->value.str );
	if( ref ){ return PackABX( OP_MOV, dest_reg, src_reg ); }
	ref = GlobalGet( &src_reg, var->value.str );
	if( ref ){ return PackABX( OP_LOADG, dest_reg, src_reg ); }
	I8 *val = ArenaOff( GetStrings( ), var->value.str->offset );
	Throw( "Assignment to undefined reference: %s\n", val );
	return 0;
}

U32 AssignCall( U8 dest_reg, Var *var )
{
	return 0;
}

U32 Assign( U8 dest_reg, Var *var, ParseType T )
{
	static Label *types[ ] = { &&CONST, &&REF, &&CALL };
	goto *types[ T ];
	CONST: return AssignConst( dest_reg, var );
	REF: return AssignRef( dest_reg, var );
	CALL: return AssignCall( dest_reg, var );
}

U32 GlobalAssign( U8 dest_reg, Var *var, String *name, ParseNode *rhs )
{
	if( !var ){ var = GlobalPush( &dest_reg, name, rhs->value ); }
	var->value = rhs->value;
	return Assign( dest_reg, var, rhs->type );
}

U32 LocalAssign( Func *fn, String *name, ParseNode *rhs )
{
	U8 dest_reg = 0;
	Var *var = LocalGet( &dest_reg, fn, name );
	if( !var ){ var = LocalPush( &dest_reg, fn, name, rhs->value ); }
	var->value = rhs->value;
	return Assign( dest_reg, var, rhs->type );
}

U32 CompileAssign( String *name, ParseNode *rhs )
{
	Compiler *compiler = GetCompiler( );
	U8 dest_reg = 0;
	Var *var = GlobalGet( &dest_reg, name );
	if( !compiler->fn ){ return GlobalAssign( dest_reg, var, name, rhs ); }
	if( var ){ return GlobalAssign( dest_reg, var, name, rhs ); } /* global assign */
	return LocalAssign( compiler->fn, name, rhs ); /* local assign */
}