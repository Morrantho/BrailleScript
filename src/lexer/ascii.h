#ifndef BS_ASCII_H
#define BS_ASCII_H

#define X_ASCII_LBL( IDX, LBL ) [ IDX ] = &&LBL,

#define ASCII( X )\
	X( 0, EOS )\
	X( 1 ... 8, ERR )\
	X( '\t', LEX )\
	X( '\n', LINE )\
	X( '\v', LEX )\
	X( '\f', LEX )\
	X( '\r', LEX )\
	X( 14 ... 31, ERR )\
	X( ' ', LEX )\
	X( '!', NOT )\
	X( '"', STR )\
	X( '#', COMMENT )\
	X( '$', ERR )\
	X( '%', MOD )\
	X( '&', BAND )\
	X( '\'', ERR )\
	X( '(', LP )\
	X( ')', RP )\
	X( '*', MUL )\
	X( '+', ADD )\
	X( ',', COM )\
	X( '-', SUB )\
	X( '.', DOT )\
	X( '/', DIV )\
	X( '0' ... '9', NUM )\
	X( ':', COL )\
	X( ';', SEMI )\
	X( '<', LT )\
	X( '=', EQ )\
	X( '>', GT )\
	X( '?', ERR )\
	X( '@', RET )\
	X( 'A' ... 'Z', ID )\
	X( '[', LS )\
	X( '\\', ERR )\
	X( ']', RS )\
	X( '^', BXOR )\
	X( '_', ID )\
	X( '`', ERR )\
	X( 'a' ... 'z', ID )\
	X( '{', LC )\
	X( '|', BOR )\
	X( '}', RC )\
	X( '~', BNOT )\
	X( 127, ERR )

#endif