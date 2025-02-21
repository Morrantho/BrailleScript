Void IoRead( Arena *src, I8 *file )
{
	FILE *stream = fopen( file, "rb" );
	if( !stream ){ Throw( "File not found: %s\n", file ); }
	fseek( stream, 0, SEEK_END );
	long len = ftell( stream );
	fseek( stream, 0, SEEK_SET );

	I8 *buf = ArenaOff( src, ArenaPush( src, len, 1 ) );
	U64 bytes = fread( buf, sizeof( I8 ), len, stream );
	buf[ bytes ] = '\0';
	fclose( stream );
}