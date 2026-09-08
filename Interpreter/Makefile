CC = gcc
CFLAGS = -Wall -g
OBJS = main.o lexer.o parser.o

rune: $(OBJS)
	$(CC) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o rune