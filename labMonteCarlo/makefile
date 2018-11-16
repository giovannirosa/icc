    CC     = gcc -std=c11 -g
    CFLAGS =-Wall -g
    LFLAGS =-lm

      PROG = monteCarlo
      OBJS = $(PROG).o

.PHONY: limpa faxina clean distclean purge all

%.o: %.c %.h
	$(CC) -c $(CFLAGS) $<

$(PROG):  $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

clean:
	@rm -f *~ *.bak

purge:   clean
	@rm -f *.o core a.out
	@rm -f $(PROG)
