#ifndef BS_ERR_H
#define BS_ERR_H

static jmp_buf err_jmp = { 0 };

typedef enum err_type
{
	ERRS( err_, X_ERR_ENUM )
	err_n
} err_type;

typedef struct err_info
{
	i8* name;
	i8* desc;
} err_info;

typedef struct err
{
	i8* name;
	i8* file;
	u32 line;
	u32 col;
} err;

stil const err_info* err_get( err_type type )
{
	static const err_info errors[ err_n ] = { ERRS( err_, X_ERR_FMT ) };
	return &errors[ type ];
}

/* Only used for unrecoverable errors, where "bslog" isn't suitable. */
void err_throw( err_type type, ... )
{
	const err_info* info = err_get( type );
	fprintf( stderr, "%s, ", info->name );
	va_list args;
	va_start( args, type );
	vfprintf( stderr, info->desc, args );
	va_end( args );
	longjmp( err_jmp, type );
}

#endif