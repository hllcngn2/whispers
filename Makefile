whispers:
	gcc -o Whispers \
			main.c \
		       	drawsmallmap.c \
					-lncurses

clean:
	rm Whispers.exe Whispers.exe.stackdump

.PHONY: whispers
