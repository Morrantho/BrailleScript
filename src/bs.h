#include <stdint.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <signal.h>
#include <math.h>

#include "fwd.h"

#include "std/offset.h"
#include "std/value.h"
#include "std/arena.h"
#include "std/vec.h"
#include "std/string.h"
#include "std/table.h"
#include "std/map.h"

#include "bslog/errs.h"
#include "bslog/err.h"
#include "bslog/bslog.h"

#include "lexer/ascii.h"
#include "lexer/tokens.h"
#include "lexer/token.h"
#include "lexer/lexer.h"

#include "parser/stmts.h"
#include "parser/precs.h"
#include "parser/exprs.h"
#include "parser/states.h"
#include "parser/ir.h"
#include "parser/parser.h"

#include "compiler/opcodes.h"
#include "compiler/op.h"
#include "compiler/unafold.h"
#include "compiler/binfold.h"
#include "compiler/compiler.h"

#include "heap/heap.h"

struct bs
{
	heap heap;
	bslog log;
	lexer lexer;
	parser parser;
	compiler compiler;
};
