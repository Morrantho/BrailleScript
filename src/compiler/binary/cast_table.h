static Label *types[ VALUE_N ][ VALUE_N ] =
{
	[ VALUE_I64 ] =
	{
		[ VALUE_I64 ] = &&I64_I64,
		[ VALUE_F64 ] = &&I64_F64,
		[ VALUE_STR ] = &&I64_STR,
	},

	[ VALUE_F64 ] =
	{
		[ VALUE_I64 ] = &&F64_I64,
		[ VALUE_F64 ] = &&F64_F64,
		[ VALUE_STR ] = &&F64_STR,
	},

	[ VALUE_STR ] =
	{
		[ VALUE_I64 ] = &&STR_I64,
		[ VALUE_F64 ] = &&STR_F64,
		[ VALUE_STR ] = &&STR_STR,
	}
};