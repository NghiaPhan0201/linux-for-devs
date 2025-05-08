CC = gcc
AR = ar rcs
CFLAGS = -Wall

.PHONY: all clean run

all: lib/libcalc.a

lib/libcalc.a: obj/calc_add.o obj/calc_sub.o obj/calc_mul.o obj/calc_div.o
	mkdir -p lib
	$(AR) lib/libcalc.a obj/*.o

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

run: lib/libcalc.a
	$(CC) main.c -Icalc -Llib -lcalc -o test_static
	./test_static

clean:
	rm -rf obj lib test_static