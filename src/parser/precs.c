void prec_push( parser* parser, prec prec )
{
	vec_push( parser->precs, &prec );
}

prec prec_pop( parser* parser )
{
	return *( prec* )vec_pop( parser->precs );
}

prec prec_peek( parser* parser )
{
	return *( prec* )vec_peek( parser->precs );
}
