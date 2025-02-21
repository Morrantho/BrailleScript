typedef U32 Op;

Op *OpCommit( U32 *idx )
{
	Compiler *compiler = GetCompiler( );
	Vec *code = GetCode( );
	if( compiler->fn ){ compiler->fn->ncode++; }
	*idx = code->len;
	return VecCommit( code );
}

U32 *OpGet( U32 idx )
{
	return VecGet( GetCode( ), idx );
}

U32 PackAB( U8 O, U16 A, U16 B )
{
	U32 idx;
	*( OpCommit( &idx ) ) =
		( ( O & 63 )   << 26 ) | /* 6 */
		( ( A & 8191 ) << 13 ) | /* 13 */
		( ( B & 8191 ) );		 /* 13 */
	return idx;
}

U32 PackABC( U8 O, U8 A, U16 B, U16 C )
{ /* op: 6, a: 8, b: 9, c: 9 */
	U32 idx;
	*( OpCommit( &idx ) ) =
		( ( O & 63 )  << 26 ) | /* 6 */
		( ( A & 255 ) << 18 ) | /* 8 */
		( ( B & 511 ) << 9 )  | /* 9 */
		( ( C & 511 ) );		/* 9 */
	return idx;
}

U32 PackABX( U8 O, U8 A, U32 BX )
{ /* op: 6, a: 8, b: unsigned 18 */
	U32 idx;
	*( OpCommit( &idx ) ) =
		  ( ( O  & 63 )  << 26 ) |	/* 6 */
		  ( ( A  & 255 ) << 18 ) |	/* 8 */
		  ( ( BX & 262143 ) );		/* 18 */
	return idx;
}

U32 PackASBX( U8 O, U8 A, I32 SBX )
{ /* op: 6, a: 8, b: signed 18 */
	U32 idx;
	U32 bias = SBX + 131071;
	*( I32* )( OpCommit( &idx ) ) =
		  ( ( O   & 63 )  << 26 ) | /* 6 */
		  ( ( A   & 255 ) << 18 ) | /* 8 */
		  ( ( bias & 262143 ) );	/* 18 */
	return idx;
}

U32 PackAX( U8 O, U32 AX )
{ /* op: 6, a: 26 */
	U32 idx;
	*( OpCommit( &idx ) ) =
		( ( O & 63 ) << 26 ) | /* 6 */
		( ( AX & 67108863 ) ); /* 26 */
	return idx;
}

Void OpLog( Op *op )
{
	U8 O   = ( *op >> 26 ) & 63;  /* 6 */
	U16 A  = ( *op >> 18 ) & 255; /* 8 */
	U16 BX = ( *op ) & 262143;	  /* 18 */
	I8 *S = OpToStr( O );
	printf( "%s A[ %d ] BX[ %d ]\n", S, A, BX );
}

Void OpLogAll( )
{
	Vec *code = GetCode( );
	for( U32 i = 0; i < code->len; i++ )
	{
		OpLog( VecGet( code, i ) );
	}
}