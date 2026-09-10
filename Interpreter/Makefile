CC = gcc
CFLAGS = -g
SRCDIR = src
OBJDIR = compiled

OBJS = $(OBJDIR)/main.o $(OBJDIR)/lexer.o $(OBJDIR)/parser.o

rune: $(OBJS)
	$(CC) -o $@ $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o rune

.PHONY: clean   