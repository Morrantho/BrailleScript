void pstate_push( parser* parser, parse_state type )
{
	vec_push( parser->states, &type );
}

parse_state pstate_pop( parser* parser )
{
	return *( parse_state* )vec_pop( parser->states );
}
