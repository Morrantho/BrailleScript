#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <setjmp.h>
#include <signal.h>
#include <stdint.h>
#include <math.h>

#include "std/types.h"
#include "std/endian.h"
#include "std/err.h"
#include "std/arena.h"
#include "std/vec.h"
#include "std/string.h"
#include "std/value.h"
#include "std/table.h"
#include "std/map.h"
#include "std/env.h"
#include "std/io.h"

#include "lexer/token_type.h"
#include "lexer/lexer.h"

#include "parser/prec.h"
#include "parser/parse_type.h"
#include "parser/parser.h"

#include "compiler/opcode.h"
#include "compiler/compiler.h"
#include "compiler/op.h"
#include "compiler/assign/assign.h"
#include "compiler/unary/eval.h"
#include "compiler/unary/unary.h"
#include "compiler/binary/eval.h"
#include "compiler/binary/binary.h"

#include "mem.h"
#include "main.h"