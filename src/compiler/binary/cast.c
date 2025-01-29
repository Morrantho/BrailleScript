stil void bin_i64_to_i64( ir* ir )
{
	/* nothing to do */
}

stil void bin_i64_to_f64( ir* ir )
{
	ir->value.f64 = ( f64 )ir->value.i64;
}

stil void bin_i64_to_str( ir* ir )
{
	/* error or build runtime string */
}

stil void bin_f64_to_i64( ir* ir )
{
	ir->value.i64 = ( i64 )ir->value.f64;
}

stil void bin_f64_to_f64( ir* ir )
{
	/* nothing to do */
}

stil void bin_f64_to_str( ir* ir )
{
	/* error or build runtime string */
}

stil void bin_str_to_i64( ir* ir )
{
	/* error or build runtime string */
}

stil void bin_str_to_f64( ir* ir )
{
	/* error or build runtime string */
}

stil void bin_str_to_str( ir* ir )
{
	/* nothing to do */
}

/* Cast an ir node to a common type, also updating its value_type.  */
stil void bin_cast( ir* ir, value_type common )
{
	static void* types[ value_n * value_n ] =
	{
		VALUE_TYPES( &&bin_, _to_, X_VALUE_VALUE )
	};
	ir->value.type = common;
	u32 idx = ir->value.type * value_n + common;
	goto *types[ idx ];
	VALUE_TYPES( bin_, _to_, X_VALUE_VALUE_FN )
}