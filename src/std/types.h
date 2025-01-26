#ifndef BS_TYPES_H
#define BS_TYPES_H

#define stil static inline
#define X_TYPE_DEF( T, V ) typedef T V;
#define X_TYPE_STRUCT( T, V ) V V;

/* WARNING: DO NOT USE "p2void". It's not a double pointer: void** */
/* It's a triple pointer: void*** */
#define TYPES( X )\
	X( void*, pvoid )\
	X( char, i8 )\
	X( short, i16 )\
	X( int, i32 )\
	X( long, i64 )\
	X( int8_t, s8 )\
	X( int16_t, s16 )\
	X( int32_t, s32 )\
	X( int64_t, s64 )\
	X( uint8_t, u8 )\
	X( uint16_t, u16 )\
	X( uint32_t, u32 )\
	X( uint64_t, u64 )\
	X( float, f32 )\
	X( double, f64 )

typedef void lbl;

TYPES( X_TYPE_DEF )

#endif