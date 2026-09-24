CC = gcc
CFLAGS = -g
SRCDIR = src
OBJDIR = compiled

ifeq ($(OS),Windows_NT)
    TARGET = rune.exe
    RM = if exist "$(OBJDIR)" rmdir /s /q "$(OBJDIR)"
    MKDIR = if not exist "$(dir $@)" mkdir "$(dir $@)"
    SRCS := $(shell powershell -NoProfile -Command "Get-ChildItem -Path '$(SRCDIR)' -Recurse -File -Filter '*.c' | ForEach-Object { $$_.FullName.Substring((Get-Location).Path.Length + 1).Replace('\\','/') }")
else
    TARGET = rune
    RM = rm -rf $(OBJDIR)
    MKDIR = mkdir -p $(dir $@)
    SRCS := $(shell find $(SRCDIR) -name '*.c')
endif

OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

$(OBJDIR)/%.o: %.c
	@$(MKDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM)
	-del /f /q "$(TARGET)" 2>nul
	-rm -f $(TARGET) 2>nul

.PHONY: clean