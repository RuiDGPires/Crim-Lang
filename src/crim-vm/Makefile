NAME = crim-vm
CC=gcc
CFLAGS=-I.
DEPS = env.h hashtable/hashtable.h hashtable/superfasthash.h hashtable/linkedlistint.h virtualmachine.h
OFILES = env.o hashtable/hashtable.o hashtable/superfasthash.o hashtable/linkedlistint.o virtualmachine.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OFILES) 
	$(CC) -o $(NAME) $(OFILES) -lm

clean:
	rm -f *.o /hashtable/*.o $(NAME)

g:
	$(CC) -g -o $(NAME) $(OFILES)