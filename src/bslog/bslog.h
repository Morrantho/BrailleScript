#define LOG_BUF 231

struct bslog
{
	i8* file;
	arena* logstrs; /* arena< err > */
	vec* logs; /* vec< u32 > */
	u32 line;
	u32 col;
};

void log_init( bslog* log, heap* heap, i8* file );
void log_reset( bslog* log );
u32 log_err( bslog* log, err_type type, ... );
void log_all( bslog* log );
