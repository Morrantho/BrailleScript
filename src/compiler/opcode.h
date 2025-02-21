#define X_OPCODE_ENUM( ENUM, PACKFN ) ENUM,
#define X_OPCODE_STR( ENUM, PACKFN ) #ENUM,

#define OPCODE_LIST( PFX, X )\
	/* Unary */\
	X( PFX##NOP, NULL )\
	X( PFX##NOT, PackABC )\
	X( PFX##BNOT, PackABC )\
	X( PFX##PREINC, PackABC )\
	X( PFX##PREDEC, PackABC )\
	X( PFX##POSTINC, PackABC )\
	X( PFX##POSTDEC, PackABC )\
	/* Binary Arithmetic */\
	X( PFX##ADD, PackABC )\
	X( PFX##SUB, PackABC )\
	X( PFX##MUL, PackABC )\
	X( PFX##DIV, PackABC )\
	X( PFX##MOD, PackABC )\
	X( PFX##POW, PackABC )\
	/* Binary Bitwise Arithmetic */\
	X( PFX##BAND, PackABC )\
	X( PFX##BOR, PackABC )\
	X( PFX##BXOR, PackABC )\
	X( PFX##LSH, PackABC )\
	X( PFX##RSH, PackABC )\
	/* Binary Relational */\
	X( PFX##EQ, PackABC )\
	X( PFX##NEQ, PackABC )\
	X( PFX##LT, PackABC )\
	X( PFX##LE, PackABC )\
	X( PFX##GT, PackABC )\
	X( PFX##GE, PackABC )\
	/* Binary Logical */\
	X( PFX##AND, PackABC )\
	X( PFX##OR, PackABC )\
	/* Binary Assignments */\
	X( PFX##MOV, PackABC )\
	X( PFX##ADDEQ, PackABC )\
	X( PFX##SUBEQ, PackABC )\
	X( PFX##MULEQ, PackABC )\
	X( PFX##DIVEQ, PackABC )\
	X( PFX##MODEQ, PackABC )\
	X( PFX##POWEQ, PackABC )\
	X( PFX##BANDEQ, PackABC )\
	X( PFX##BOREQ, PackABC )\
	X( PFX##BXOREQ, PackABC )\
	X( PFX##LSHEQ, PackABC )\
	X( PFX##RSHEQ, PackABC )\
	/* Loading */\
	X( PFX##LOADC, PackABX )\
	X( PFX##LOADG, PackABX )

typedef enum OpCode
{
	OPCODE_LIST( OP_, X_OPCODE_ENUM )
	OP_N
} OpCode;

/* TODO: Add debug only. Waste of space in release. */
I8 *OpToStr( OpCode op )
{
	static I8 *strings[ OP_N ] = { OPCODE_LIST( , X_OPCODE_STR ) };
	return strings[ op ];
}