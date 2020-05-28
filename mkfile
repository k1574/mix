<mkconfig

SRC = `{ls *.c}
#HDR = `{ls *.h}
OBJ = ${SRC:%.c=%.o}
TGT = $NAME

all :Q: $TGT 
	echo -n
$TGT : $OBJ
	$LD $LDFLAGS -o $target $prereq
%.o :V: %.c
	$CC $CFLAGS -c -o $target $prereq
%.c : $HDR
	touch $target
%.h :
	touch $target
clean :V:
	rm -rf $TGT *.o
install :V: $TGT
	cp -f $TGT $BIN/
	chmod 0755 $BIN/$TGT
uninstall :V:
	rm -f $BIN/$TGT
