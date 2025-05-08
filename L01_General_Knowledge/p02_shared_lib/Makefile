CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS = -shared

.PHONY: all clean run

all: lib/libcalc.so

lib/libcalc.so: obj/calc_add.o obj/calc_sub.o obj/calc_mul.o obj/calc_div.o
	mkdir -p lib
	$(CC) $(LDFLAGS) obj/calc_add.o obj/calc_sub.o obj/calc_mul.o obj/calc_div.o -o lib/libcalc.so

obj/calc_add.o: calc/calc_add.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c calc/calc_add.c -o obj/calc_add.o

obj/calc_sub.o: calc/calc_sub.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c calc/calc_sub.c -o obj/calc_sub.o

obj/calc_mul.o: calc/calc_mul.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c calc/calc_mul.c -o obj/calc_mul.o

obj/calc_div.o: calc/calc_div.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c calc/calc_div.c -o obj/calc_div.o

run: lib/libcalc.so
	$(CC) main.c -Icalc -Llib -lcalc -o test_shared
	LD_LIBRARY_PATH=lib ./test_shared

clean:
	rm -rf obj lib test_shared