void io_read( arena* arena, i8* file )
{
	FILE* stream = fopen( file, "rb" );
	if( !stream ){ err_throw( err_file, file ); }
	fseek( stream, 0, SEEK_END );
	u32 len = ftell( stream );
	fseek( stream, 0, SEEK_SET );
	u32 offset = arena_alloc( arena, len + 1, 1 );
	i8* dest = arena_ptr( arena, offset );
	u32 bytes = fread( dest, sizeof( i8 ), len, stream );
	dest[ bytes ] = '\0';
	fclose( stream );
}
