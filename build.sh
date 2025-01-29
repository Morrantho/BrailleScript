rm -f bin/*

CC="gcc"
SRC="src/bs/bs.c"
OBJ="bin/bs.s"
BIN="bin/bs"
ASM="-S -masm=intel -fverbose-asm"
STD="-std=c2x"
FAST="-Ofast -flto -fwhole-program"
WARN="-Wall -Wextra -Wno-override-init "
WARN=$WARN"-Wno-unused-variable -Wno-unused-parameter"
LIB="-lm"
DUMP="bin/bs_dump.s"

if [ "$1" == "dbg" ]; then
	$CC $SRC $ASM $WARN $STD -g -o $OBJ # compile to asm
	$CC $OBJ -g -o $BIN $LIB # link
	objdump -d -M intel $BIN > $DUMP
fi

if [ "$1" == "fdbg" ]; then
	$CC $SRC $ASM $WARN $STD -g -o $OBJ # compile to asm
	$CC $OBJ $FAST -g -o $BIN $LIB # link
	objdump -d -M intel $BIN > $DUMP
fi

if [ "$1" == "rel" ]; then
	$CC $SRC $ASM $WARN $STD $FAST -s -o $OBJ # compile to asm
	$CC $OBJ $FAST -s -o $BIN $LIB # link
	objdump -d -M intel $BIN > $DUMP
fi