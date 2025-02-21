jmp_buf *GetJmp( )
{
	static jmp_buf buf = { 0 };
	return &buf;
}

Void Throw( I8 *fmt, ... )
{
	va_list args;
	va_start( args, fmt );
	vfprintf( stderr, fmt, args );
	va_end( args );
	longjmp( *GetJmp( ), 1 );
}