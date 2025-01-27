enum err_type
{
	ERRS( err_, X_ERR_ENUM )
	err_n
};

struct err_info
{
	i8* name;
	i8* desc;
};

struct err
{
	i8* name;
	i8* file;
	u32 line;
	u32 col;
};

const err_info* err_get( err_type type );
void err_throw( err_type type, ... );
