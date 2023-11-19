testlvl:
	gcc	src/testlvl2.c \
		\
		src/c2buf/c2buf.c \
		src/c2buf/c2brush.c \
				-Isrc/inc -lncurses
