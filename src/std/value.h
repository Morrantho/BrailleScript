#ifndef BS_VALUE_H
#define BS_VALUE_H

#define X_VALUE_ENUM( OP, ENUM ) ENUM,
#define X_VALUE_NAME( OP, ENUM ) ENUM

#define VALUE_TYPES( OP, ENUM, X )\
	X( OP, ENUM##i64 )\
	X( OP, ENUM##f64 )\
	X( OP, ENUM##str )

#define VALUE_TYPES2( OP, ENUM, X )\
	X( OP, ENUM##i64 )\
	X( OP, ENUM##f64 )\
	X( OP, ENUM##str )

typedef enum value_type
{
	VALUE_TYPES( op_, value_, X_VALUE_ENUM )
	value_n
} value_type;

typedef struct value
{
	value_type type;
	union
	{
		i64 i64;
		f64 f64;
		str* str;
	};
} value;

#endif