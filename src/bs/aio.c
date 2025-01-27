#include "aio.h"
#include "../std/offset.c"
#include "../std/arena.c"
#include "../std/vec.c"
#include "../std/string.c"
#include "../std/table.c"
#include "../std/map.c"
#include "../io/io.c"
#include "../bslog/err.c"
#include "../bslog/bslog.c"
#include "../lexer/token.c"
#include "../lexer/lexer.c"
#include "../parser/states.c"
#include "../parser/precs.c"
#include "../parser/ir.c"
#include "../parser/parser.c"
#include "../compiler/op.c"
#include "../compiler/unafold.c"
#include "../compiler/binfold.c"
#include "../compiler/compiler.c"
#include "../heap/heap.c"