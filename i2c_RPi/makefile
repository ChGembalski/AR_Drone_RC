CC = gcc

CFLAGS = -c -Wall -O3

LDFLAGS = 

SOURCES=$(shell find ./ -name *.c)

OBJECTS=$(SOURCES:%.c=%.o)

EXECUTABLE=testi2c

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
