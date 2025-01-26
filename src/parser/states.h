#ifndef BS_PARSE_STATES_H
#define BS_PARSE_STATES_H

#define X_PS_ENUM( ENUM, LBL ) ENUM,
#define X_PS_STR( ENUM, LBL ) #ENUM,
#define X_PS_LBL( ENUM, LBL ) [ ENUM ] = &&LBL,

#define PARSE_STATES( V, X )\
	X( V##err, ERR )\
	X( V##stmt, STMT )\
	X( V##expr, EXPR )\
	X( V##unary_end, UNARY_END )\
	X( V##group_end, GROUP_END )\
	X( V##binary_end, BINARY_END )\
	X( V##fn_body, FN_BODY )\
	X( V##fn_end, FN_END )

typedef enum parse_state
{
	PARSE_STATES( ps_, X_PS_ENUM )
	ps_n
} parse_state;

#endif
