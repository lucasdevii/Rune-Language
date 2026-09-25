CC = gcc

CFLAGS = -Wall -Wextra -g -I. -Isrc

SRC = $(wildcard src/*.c) \
      $(wildcard src/stager/*.c)  \
      $(wildcard src/stages/token_helpers/*.c)

OBJ = $(SRC:.c=.o)

TARGET = rune

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)