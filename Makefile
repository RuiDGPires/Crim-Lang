CC=gcc
CFLAGS=-I.
DEPS = tokeniser/tokenlib.h tokeniser/lexer.h parser/parser.h parser/syntaxtree.h evaluator/env.h evaluator/hashtable/hashtable.h evaluator/hashtable/superfasthash.h evaluator/hashtable/linkedlistint.h evaluator/virtualmachine.h
OFILES = tokeniser/lexer.o tokeniser/tokenlib.o parser/parser.o parser/syntaxtree.o evaluator/env.o evaluator/hashtable/hashtable.o evaluator/hashtable/superfasthash.o evaluator/hashtable/linkedlistint.o evaluator/virtualmachine.o main.o 
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

make: $(OFILES)
	$(CC) -o crim $(OFILES)

clean:
	rm -f *.o parser/*.o tokeniser/*.o evaluator/*.o evaluator/hashtable/*.o crim

g:
	$(CC) -g -o crim $(OFILES)