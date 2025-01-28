void ir_logeval( ir* evald )
{
	if( evald->type == ir_none ){ return; }
	switch( evald->value.type )
	{
		case value_i64:
			printf( "%ld\n", evald->value.i64 ); break;
		case value_f64:
			printf( "%f\n", evald->value.f64 ); break;
		case value_str:
			printf( "%s\n", ( u8* )( evald->value.str + 1 ) );
			break;
		default: break;
	}
	evald->type = ir_none;
}

ir* ir_push( parser* parser, ir_type it, value_type vt, void* value )
{
	ir* pir = vec_commit( parser->irs );
	pir->type = it;
	pir->value.type	= vt;
	switch( vt )
	{
		case value_i64: pir->value.i64 = *( i64* )value; return pir;
		case value_f64: pir->value.f64 = *( f64* )value; return pir;
		case value_str: pir->value.str = ( str* )value; return pir;
		default: return pir;
	}
}
