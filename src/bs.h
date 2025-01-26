#ifndef BS_H
#define BS_H

#include <stdint.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <signal.h>
#include <math.h>

#include "std/types.h"
#include "std/offset.h"
#include "std/vec.h"
#include "std/arena.h"
#include "std/string.h"
#include "std/table.h"
#include "std/value.h"
#include "std/map.h"

/* forward declarations */
#include "lexer/tokens.h"
#include "lexer/token.h"

#include "parser/states.h"
#include "parser/precs.h"
#include "parser/parse_rule.h"

#include "compiler/opcodes.h"
#include "compiler/op.h"

#include "parser/ir.h"
/* end forward declarations */

#include "heap/heap.h"

#include "bslog/errs.h"
#include "bslog/err.h"
#include "bslog/bslog.h"

#include "io/io.h"

#include "lexer/ascii.h"
#include "lexer/lexer.h"

#include "parser/stmts.h"
#include "parser/exprs.h"
#include "parser/parser.h"

#include "compiler/unafold.h"
#include "compiler/binfold.h"
#include "compiler/compiler.h"

typedef struct bs
{
	heap heap; /* all heap allocs go here */
	bslog log;
	lexer lexer;
	compiler compiler;
	parser parser;
} bs;

#endif