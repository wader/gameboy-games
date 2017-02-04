CC	= ../../../bin/lcc -Wa-l -Wl-m

BINS	= slippy.gb

all:	$(BINS)

%.o:	%.c
	$(CC) -c -o $@ $<

%.o:	%.s
	$(CC) -c -o $@ $<

%.gb:	%.o
	$(CC) -Wl-yn\=\"Slippy\" -o $@ $<

clean:
	rm -f *.o *.lst *.map *.gb



