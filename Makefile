CC=gcc
CFLAGS=-I.
DEPS = tokeniser/tokenlib.h tokeniser/lexer.h parser/parser.h parser/syntaxtree.h vm/env.h vm/hashtable/hashtable.h vm/hashtable/superfasthash.h vm/hashtable/linkedlistint.h vm/virtualmachine.h
OFILES = tokeniser/lexer.o tokeniser/tokenlib.o parser/parser.o parser/syntaxtree.o vm/env.o vm/hashtable/hashtable.o vm/hashtable/superfasthash.o vm/hashtable/linkedlistint.o vm/virtualmachine.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

make: $(OFILES)
	$(CC) -o crim $(OFILES) -lm

clean:
	rm -f *.o parser/*.o tokeniser/*.o evaluator/*.o vm/*.o vm/hashtable/*.o crim

g:
	$(CC) -g -o crim $(OFILES)