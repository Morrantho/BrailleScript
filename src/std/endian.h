#if __BYTE_ORDER__
	#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		#define ENDIAN_BIG __ORDER_BIG_ENDIAN__
	#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		#define ENDIAN_LIL __ORDER_LITTLE_ENDIAN__
	#endif
#else
	#error "Cannot determine Endianness."
#endif