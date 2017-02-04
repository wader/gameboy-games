CC	= ../../../bin/lcc -Wa-l -Wl-m

BINS	= minesweeper.gb

all:	$(BINS)

%.o:	%.c
	$(CC) -c -o $@ $<

%.o:	%.s
	$(CC) -c -o $@ $<

%.gb:	%.o
	$(CC) -Wl-yn\=\"Minesweeper\" -o $@ $<

clean:
	rm -f *.o *.lst *.map *.gb


