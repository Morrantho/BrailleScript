CC=gcc
ASM="-S -fverbose-asm -masm=intel"
WARN="-Wall -Wextra"
NOWARN="-Wno-unused-parameter -Wno-unused-variable -Wno-override-init"
STD="-std=c2x"
REL="-Ofast -flto -fwhole-program -s -DNDEBUG"
DBG="-g -O0 -DDEBUG"
BIN="bs"
OBJ=$BIN.s
SRC=$BIN.c
LIB="-lm"

REL_CMP="$CC $ASM $WARN $NOWARN $STD $REL src/$SRC -o bin/$OBJ"
REL_LNK="$CC $REL bin/$OBJ -o bin/$BIN $LIB"

DBG_CMP="$CC $ASM $WARN $NOWARN $STD $DBG src/$SRC -o bin/$OBJ"
DBG_LNK="$CC $DBG bin/$OBJ -o bin/$BIN $LIB"

[ "$1" == "rel" ] && { $REL_CMP; $REL_LNK; }
[ "$1" == "dbg" ] && { $DBG_CMP; $DBG_LNK; }
objdump -d -M intel bin/$BIN > bin/dump.s