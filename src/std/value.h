#define VALUE( T, M, V ) ( Value ){ .type = VALUE_##T, .M = V }

typedef enum ValueType
{
	VALUE_I64,
	VALUE_F64,
	VALUE_STR,
	VALUE_N
} ValueType;

typedef struct Value
{
	ValueType type;
	union
	{
		I64 i64;
		F64 f64;
		String *str;
	};
} Value;

Void ValueSet( Value *value, ValueType type, Void *data )
{
	static Label *types[ VALUE_N ] = { &&I64, &&F64, &&STR };
	goto *types[ type ];
	I64: value->i64 = *( I64* )data; return;
	F64: value->f64 = *( F64* )data; return;
	STR: value->str = data;
}