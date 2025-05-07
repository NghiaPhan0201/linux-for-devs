CC = gcc
AR = ar rcs
CFLAGS = -Wall

.PHONY: all clean run

all: create_static

create_static: create_obj
	$(AR) lib/libcalc.a obj/*.o
	mkdir -p lib

create_obj: calc/*.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c calc/*.c -o obj/*.o

run: create_static
	$(CC) main.c -Icalc -Llib -lcalc -o test_static
	./test_static

clean:
	rm -rf obj lib test_static