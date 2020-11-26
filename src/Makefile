CC=gcc
CFLAGS=-I.
CRIM = tokeniser/tokenlib.h tokeniser/lexer.h parser/parser.h parser/syntaxtree.h
VM = vm/env.h vm/hashtable/hashtable.h vm/hashtable/superfasthash.h vm/hashtable/linkedlistint.h vm/virtualmachine.h
DEPS =  $(CRIM) $(VM)
CRIM_O = tokeniser/lexer.o tokeniser/tokenlib.o parser/parser.o parser/syntaxtree.o
VM_O = vm/env.o vm/hashtable/hashtable.o vm/hashtable/superfasthash.o vm/hashtable/linkedlistint.o vm/virtualmachine.o
OFILES = $(CRIM_O) $(VM_O) main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OFILES) 
	$(CC) -o crim $(OFILES) -lm

crim: $(CRIM_O) main.o 
	$(CC) -o crim $(CRIM_O) main.o  -lm

clean:
	rm -f *.o parser/*.o tokeniser/*.o evaluator/*.o vm/*.o vm/hashtable/*.o crim

g:
	$(CC) -g -o crim $(OFILES)