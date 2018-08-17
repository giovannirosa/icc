    CC     = gcc -g

    CFLAGS = -std=c11
    LFLAGS = -lm

      PROG = labZero
      OBJS = utils.o \
             ZeroFuncao.o

.PHONY: limpa faxina clean purge distclean all

%.o: %.c %.h utils.h
	$(CC) -c $(CFLAGS) $<

$(PROG):  $(OBJS) $(PROG).o
	$(CC) -o $@ $^ $(LFLAGS)

limpa:
	@rm -f *~ *.bak

faxina:   clean
	@rm -f *.o core a.out
	@rm -f $(PROG)
