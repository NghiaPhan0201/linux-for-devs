CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS = -shared

.PHONY: all clean run create_obj create_shared

all: create_shared

create_shared: create_obj
	mkdir -p lib
	$(CC) $(LDFLAGS) obj/*.o -o lib/libcalc.so

obj/%.o: calc/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

create_obj: $(patsubst calc/%.c,obj/%.o,$(wildcard calc/*.c))

run: create_shared
	$(CC) main.c -Icalc -Llib -lcalc -o test_shared
	LD_LIBRARY_PATH=lib ./test_shared

clean:
	rm -rf obj lib test_shared