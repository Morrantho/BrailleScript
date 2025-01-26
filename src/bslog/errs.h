#ifndef BS_ERRS_H
#define BS_ERRS_H

#define X_ERR_ENUM( ENUM, FMT ) ENUM,
#define X_ERR_FMT( ENUM, FMT ) [ ENUM ] = { .name = #ENUM, .desc = FMT },

#define ERRS( V, X )\
	X( V##none, "Ok.\n" )\
	X( V##file, "File Not Found: %s.\n" )\
	X( V##mem, "Out of memory. Couldn't allocate: %d Bytes.\n" )\
	X( V##tok, "Illegal token: %.*s.\n" )\
	X( V##str, "Unterminated String: %.*s.\n" )\
	X( V##comment, "Unterminated Comment: %.*s.\n" )\
	X( V##f64, "Malformed Float: %.*s." )\
	X( V##match, "Expected: %s, Got: %s.\n" )\
	X( V##expr, "Malformed Expression.\n" )\
	X( V##args, "Mismatched function args: %s.\n" )

#endif