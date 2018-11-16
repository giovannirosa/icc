       PROG   = matmult
       OBJS   = $(PROG).o matriz.o

       LIKWID = /home/soft/likwid
 LIKWID_FLAGS = -DLIKWID_PERFMON -I$(LIKWID)/include
  LIKWID_LIBS = -L$(LIKWID)/lib -llikwid

        CC = gcc -std=c11
    CFLAGS = $(LIKWID_FLAGS)
    LFLAGS = $(LIKWID_LIBS) -lm

.PHONY: clean limpa purge faxina distclean debug avx

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

$(PROG):  $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

avx: CFLAGS += -O3
debug: CFLAGS += -DDEBUG -g
avx debug: $(PROG)

clean:
	@rm -f *~ *.bak *.tmp

purge distclean:   clean
	@rm -f  $(PROG) *.o core a.out
	@rm -f *.png
