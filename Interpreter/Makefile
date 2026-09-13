CC = gcc
CFLAGS = -g
SRCDIR = src
OBJDIR = compiled

SRCS = $(shell find $(SRCDIR) -name '*.c')
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

rune: $(OBJS)
	$(CC) -o $@ $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	rm -f rune

.PHONY: clean