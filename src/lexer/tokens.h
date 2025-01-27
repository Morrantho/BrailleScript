#define X_TOKEN_ENUM( ENUM ) ENUM,
#define X_TOKEN_STR( ENUM ) #ENUM,
#define X_TOKEN_LBL( ENUM ) &&LBL_##ENUM,

#define TOKENS( V, X )\
	X( V##eof ) /* \0 */\
	\
	X( V##add ) /* + */\
	X( V##addeq ) /* += */\
	X( V##addadd ) /* ++ */\
	\
	X( V##sub ) /* - */\
	X( V##subeq ) /* -= */\
	X( V##subsub ) /* -- */\
	\
	X( V##mul ) /* * */\
	X( V##muleq ) /* *= */\
	X( V##pow ) /* ** */\
	\
	X( V##div ) /* / */\
	X( V##diveq ) /* /= */\
	\
	X( V##mod ) /* % */\
	X( V##modeq ) /* %= */\
	\
	X( V##band ) /* & */\
	X( V##bandeq ) /* &= */\
	X( V##and ) /* && */\
	\
	X( V##bor ) /* | */\
	X( V##boreq ) /* |= */\
	X( V##or ) /* || */\
	\
	X( V##bxor ) /* ^ */\
	X( V##bxoreq ) /* ^= */\
	\
	X( V##lt ) /* < */\
	X( V##le ) /* <= */\
	X( V##lsh ) /* << */\
	X( V##lsheq ) /* <<= */\
	X( V##break ) /* <<: */\
	\
	X( V##gt ) /* > */\
	X( V##ge ) /* >= */\
	X( V##rsh ) /* >> */\
	X( V##rsheq ) /* >>= */\
	\
	X( V##eq ) /* = */\
	X( V##eqeq ) /* == */\
	\
	X( V##not ) /* ! */\
	X( V##neq ) /* != */\
	\
	X( V##bnot ) /* ~ */\
	X( V##len ) /* # */\
	X( V##ret ) /* return */\
	\
	X( V##lp ) /* ( */\
	X( V##rp ) /* ) */\
	X( V##ls ) /* [ */\
	X( V##rs ) /* ] */\
	X( V##lc ) /* { */\
	X( V##rc ) /* } */\
	\
	X( V##dot ) /* . */\
	X( V##else ) /* .. */\
	X( V##if ) /* .: */\
	X( V##for ) /* .; */\
	\
	X( V##col ) /* : */\
	X( V##end ) /* :: */\
	X( V##then ) /* :. */\
	X( V##cont ) /* :>> */\
	\
	X( V##semi ) /* ; */\
	X( V##while ) /* ;; */\
	X( V##do ) /* ;. */\
	X( V##com ) /* , */\
	\
	X( V##i64 ) /* 0-9 */\
	X( V##f64 ) /* 0-9. */\
	X( V##str ) /* " */\
	X( V##id ) /* a-zA-Z0-9_ */
