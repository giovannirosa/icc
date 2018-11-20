    CC     = gcc -std=c11 -g
    CFLAGS =-Wall -O3 -mavx -march=native $(LIKWID_FLAGS)
    LFLAGS =-lm $(LIKWID_LIBS)

LIKWID = /home/soft/likwid
LIKWID_FLAGS = -DLIKWID_PERFMON -I$(LIKWID)/include
LIKWID_LIBS = -L$(LIKWID)/lib -llikwid

      PROG = cgSolver
      OBJS = utils.o \
             conjGradient.o \
	  		 $(PROG).o

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
