static Label *irs[ PT_N ][ PT_N ] =
{
	[ PT_CONST ] =
	{
		[ PT_CONST ] = &&CONST_CONST,
		[ PT_REF ] = &&CONST_REF,
		[ PT_CALL ] = &&CONST_CALL,
	},

	[ PT_REF ] =
	{
		[ PT_CONST ] = &&REF_CONST,
		[ PT_REF ] = &&REF_REF,
		[ PT_CALL ] = &&REF_CALL,
	},

	[ PT_CALL ] =
	{
		[ PT_CONST ] = &&CALL_CONST,
		[ PT_REF ] = &&CALL_REF,
		[ PT_CALL ] = &&CALL_CALL,
	}
};