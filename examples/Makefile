CPPFLAGS = -I../include 
CFLAGS   = $(CPPFLAGS)
LDFLAGS  =

all: tests check

tests: test/tests.o test/factorial.o factorial.o
	$(CC) -o $@ $^ $(LDFLAGS)

check:
	./tests

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<
