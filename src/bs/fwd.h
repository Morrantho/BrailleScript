/* Noone wants to see these anywhere else. */
#define stil static inline
typedef char i8;
typedef short i16;
typedef int i32;
typedef long i64;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;
typedef void lbl;

typedef struct offset offset;
typedef enum value_type value_type;
typedef struct value value;
typedef struct arena arena;
typedef struct vec vec;
typedef struct str str;
typedef struct str_res str_res;
typedef struct table table;
typedef struct table_res table_res;
typedef struct entry entry;
typedef struct map map;
typedef entry var;
typedef map env;

typedef enum err_type err_type;
typedef struct err_info err_info;
typedef struct err err;
typedef struct bslog bslog;

typedef enum token_type token_type;
typedef struct token token;
typedef struct lexer lexer;

typedef enum prec prec;
typedef struct parse_rule parse_rule;
typedef enum parse_state parse_state;
typedef enum ir_type ir_type;
typedef struct ir ir;
typedef struct parser parser;

typedef enum opcode opcode;
typedef struct op op;
typedef struct compiler compiler;

typedef struct heap heap;

typedef struct bs bs;
