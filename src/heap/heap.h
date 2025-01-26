#ifndef BS_HEAP_H
#define BS_HEAP_H
/* This is not a heap data structure, it's a central location for all heap */
/* allocated data. This makes bookkeeping easier, and memory leaks vanish. */
#define KB( N ) ( ( N ) * 1024ULL )
#define MB( N ) ( KB( ( N ) ) * 1024ULL )

typedef struct heap
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
	// vec locals; /* vec< var >: locals */
	// vec ops; /* vec< op >: ops */
	// vec funcs; /* vec< func >: functions */
	// map globals; /* map< str, value >: globals */
	/* vm */
	// vec calls; /* vec< frame >: call stack */
	// vec vals; /* vec< value >: value stack */
} heap;

void heap_init( heap* heap )
{
	arena_init( &heap->logstrs, KB( 128 ) );
	vec_init( &heap->logs, sizeof( u32 ), 256 );
	arena_init( &heap->src, MB( 2 ) );
	arena_init( &heap->strings, KB( 256 ) );
	table_init( &heap->interns, &heap->strings, 512 );
	vec_init( &heap->pstates, sizeof( parse_state ), 512 );
	vec_init( &heap->pprecs, sizeof( prec ), 256 );
	vec_init( &heap->pirs, sizeof( ir ), KB( 64 ) / sizeof( ir ) );
	vec_init( &heap->consts, sizeof( value ), KB( 64 ) / sizeof( value ) );
}

void heap_deinit( heap* heap )
{
	free( heap->consts.base );
	free( heap->pirs.base );
	free( heap->pprecs.base );
	free( heap->pstates.base );
	free( heap->interns.base );
	free( heap->strings.base );
	free( heap->src.base );
	free( heap->logs.base );
	free( heap->logstrs.base );
}

#endif