static ValueType types[ VALUE_N ][ VALUE_N ] =
{
	[ VALUE_I64 ] =
	{
		[ VALUE_I64 ] = VALUE_I64,
		[ VALUE_F64 ] = VALUE_F64,
		[ VALUE_STR ] = VALUE_STR
	},

	[ VALUE_F64 ] =
	{
		[ VALUE_I64 ] = VALUE_F64,
		[ VALUE_F64 ] = VALUE_F64,
		[ VALUE_STR ] = VALUE_STR
	},

	[ VALUE_STR ] =
	{
		[ VALUE_I64 ] = VALUE_STR,
		[ VALUE_F64 ] = VALUE_STR,
		[ VALUE_STR ] = VALUE_STR
	}
};