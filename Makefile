.PHONY: test clean

CC = gcc
CFLAGS = -Wall
SOURCES = main.c operations.c
OBJECTS = main.o operations.o
TARGET = sed_simplified
ARGS = input.txt str/d

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)
	
*.o: $(SOURCES)
	$(CC) $(CFLAGS) $< -o $@

test: $(TARGET)
	./$(TARGET) $(ARGS)

clean: $(TARGET)
	rm -f $(OBJECTS)
