</$objtype/mkfile

BIN = /bin/games

TARG = tis99

OFILES =	main.$O \
			opcodes.$O \

HFILES =	tis100.h \

</sys/src/cmd/mkone

demo:V: all
	8.out demo/test.asm inputs0
