NAME = crim
CC=gcc
CFLAGS=-I.
DEPS = tokeniser/tokenlib.h tokeniser/lexer.h parser/parser.h parser/syntaxtree.h
OFILES = tokeniser/lexer.o tokeniser/tokenlib.o parser/parser.o parser/syntaxtree.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OFILES) 
	$(CC) -o $(NAME) $(OFILES) -lm

clean:
	rm -f *.o parser/*.o tokeniser/*.o evaluator/*.o $(NAME)

g:
	$(CC) -g -o $(NAME) $(OFILES)