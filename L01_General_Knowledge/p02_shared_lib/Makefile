CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS = -shared

.PHONY: all clean run create_obj create_shared

all: create_shared

create_shared: create_obj
	mkdir -p lib
	$(CC) $(LDFLAGS) -o lib/libcalc.so obj/*.o

create_obj: calc/*.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c calc/*.c -o obj/

run: create_shared
	$(CC) main.c -Icalc -Llib -lcalc -o test_shared
	LD_LIBRARY_PATH=lib ./test_shared

clean:
	rm -rf obj lib test_shared