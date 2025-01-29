#define X_VALUE_ENUM( ENUM ) ENUM,
/* Allows for N * N self-expansion */
#define X_VALUE_VALUE( PFX )\
	VALUE_TYPES2( PFX, , X_VALUE_ENUM )

#define X_VALUE_VALUE_FN2( ENUM ) ENUM: return ENUM( ir );
#define X_VALUE_VALUE_FN( ENUM ) VALUE_TYPES2( ENUM, , X_VALUE_VALUE_FN2 )

#define VALUE_TYPES( PFX, IFX, X )\
	X( PFX##i64##IFX )\
	X( PFX##f64##IFX )\
	X( PFX##str##IFX )
/* For self-iteration */
#define VALUE_TYPES2( PFX, IFX, X )\
	X( PFX##i64##IFX )\
	X( PFX##f64##IFX )\
	X( PFX##str##IFX )

enum value_type
{
	VALUE_TYPES( value_, , X_VALUE_ENUM )
	value_n
};

struct value
{
	value_type type;
	union
	{
		i64 i64;
		f64 f64;
		str* str;
	};
};
