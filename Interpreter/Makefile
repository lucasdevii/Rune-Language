CC = gcc
CFLAGS = -g
OBJDIR = compiled

OBJS = $(OBJDIR)/main.o $(OBJDIR)/lexer.o $(OBJDIR)/parser.o

rune: $(OBJS)
	$(CC) -o $@ $(OBJS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o rune

.PHONY: clean   