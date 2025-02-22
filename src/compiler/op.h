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
		( ( B & 8191 ) ); /* 13 */
	return idx;
}

Void UnpackAB( U32 ins, U8 *O, U16 *A, U16 *B )
{
	*O = ( ins >> 26 ) & 63; /* 6 */
	*A = ( ins >> 13 ) & 8191; /* 13 */
	*B = ( ins ) & 8191; /* 13 */
}

U32 PackABC( U8 O, U8 A, U16 B, U16 C )
{ /* OP: 6, A: 8, B: 9, C: 9 */
	U32 idx;
	*( OpCommit( &idx ) ) =
		( ( O & 63 )  << 26 ) | /* 6 */
		( ( A & 255 ) << 18 ) | /* 8 */
		( ( B & 511 ) << 9 )  | /* 9 */
		( ( C & 511 ) ); /* 9 */
	return idx;
}

Void UnpackABC( U32 ins, U8 *O, U8 *A, U16 *B, U16 *C )
{
	*O = ( ins >> 26 ) & 63; /* 6 */
	*A = ( ins >> 18 ) & 255; /* 8 */
	*B = ( ins >> 9 ) & 511; /* 9 */
	*C = ( ins ) & 511; /* 9 */
}

U32 PackABX( U8 O, U8 A, U32 BX )
{ /* op: 6, a: 8, b: unsigned 18 */
	U32 idx;
	*( OpCommit( &idx ) ) =
		  ( ( O  & 63 )  << 26 ) | /* 6 */
		  ( ( A  & 255 ) << 18 ) | /* 8 */
		  ( ( BX & 262143 ) ); /* 18 */
	return idx;
}

Void UnpackABX( U32 ins, U8 *O, U8 *A, U32 *BX )
{
	*O  = ( ins >> 26 ) & 63; /* 6 */
	*A  = ( ins >> 18 ) & 255; /* 8 */
	*BX = ( ins ) & 262143; /* 18 */
}

U32 PackASBX( U8 O, U8 A, I32 SBX )
{ /* op: 6, a: 8, b: signed 18 */
	U32 idx;
	*( OpCommit( &idx ) ) =
		( ( O   & 63 )  << 26 ) | /* 6 */
		( ( A   & 255 ) << 18 ) | /* 8 */
		( ( SBX + 131071 ) & 262143 ); /* 18 */
	return idx;
}

Void UnpackASBX( U32 ins, U8 *O, U8 *A, I32 *SBX )
{
	*O = ( ins >> 26 ) & 63; /* 6 */
	*A = ( ins >> 18 ) & 255; /* 8 */
	*SBX = ( ins & 262143 ) - 131071; /* 18 */
}

U32 PackAX( U8 O, U32 AX )
{ /* op: 6, a: 26 */
	U32 idx;
	*( OpCommit( &idx ) ) =
		( ( O & 63 ) << 26 ) | /* 6 */
		( ( AX & 67108863 ) ); /* 26 */
	return idx;
}

Void UnpackAX( U32 ins, U8 *O, U32 *A )
{
	*O = ( ins >> 26 ) & 63;
	*A = ins & 67108863;
}