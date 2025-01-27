#define KB( N ) ( ( N ) * 1024ULL )
#define MB( N ) ( KB( ( N ) ) * 1024ULL )

struct heap
{
	/* bslog */
	arena logstrs; /* arena< err > */
	vec logs; /* vec< u32 >: lex, parse, compile error stack */
	/* source */
	arena src; /* arena< u8 >: user source code */
	/* strings */
	arena strings; /* arena< str >: strings + identifiers */
	table interns; /* table< u32 >: hashes strings to offsets of heap->strings */
	/* parser */
	vec pstates; /* vec< parse_state >: parser states */
	vec pprecs; /* vec< prec >: precedence stack */
	vec pirs; /* vec< ir >: ir stack */
	/* compiler */
	vec consts; /* vec< value >: constants */
	vec vars; /* vec< var >: local vars */
	// vec ops; /* vec< op >: ops */
	// vec funcs; /* vec< func >: functions */
	// map globals; /* map< str, value >: globals */
	/* vm */
	// vec calls; /* vec< frame >: call stack */
	// vec vals; /* vec< value >: value stack */
};

void heap_init( heap* heap );
void heap_deinit( heap* heap );
