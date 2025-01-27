void ir_logeval( ir* evald )
{
	if( evald->ir_type == ir_none ){ return; }
	switch( evald->value_type )
	{
		case value_i64:
			printf( "%ld\n", evald->i64 ); break;
		case value_f64:
			printf( "%f\n", evald->f64 ); break;
		case value_str:
			printf( "%s\n", ( u8* )( evald->str + 1 ) );
			break;
		default: break;
	}
	evald->ir_type = ir_none;
}

ir* ir_push( parser* parser, ir_type it, value_type vt, void* value )
{
	ir* pir = vec_commit( parser->irs );
	pir->ir_type = it;
	pir->value_type	= vt;
	switch( vt )
	{
		case value_i64: pir->i64 = *( i64* )value; return pir;
		case value_f64: pir->f64 = *( f64* )value; return pir;
		case value_str: pir->str = ( str* )value; return pir;
		default: return pir;
	}
}
