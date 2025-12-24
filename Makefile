.PHONY: test clean

CC = gcc
CFLAGS = -Wall
SOURCES = main.c operations.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = sed_simplified
ARGS = input.txt s/Hi/prefix

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	
*.o: *.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	rm -f $(OBJECTS) $(TARGET)
