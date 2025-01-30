struct func
{	/* sizeof( 40 ) */
	str* name;
	// u32 iargs; /* start args */
	u32 nargs; /* len args */
	u32 iconsts; /* start of consts */
	u32 nconsts; /* len consts */
	u32 ivars; /* start of vars */
	u32 nvars; /* len vars */
	u32 iops; /* start of ops */
	u32 nops; /* len ops */
};

void func_next( compiler* c );