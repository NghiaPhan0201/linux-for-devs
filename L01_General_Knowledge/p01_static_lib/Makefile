CC = gcc
AR = ar rcs
CFLAGS = -Wall

.PHONY: all clean run

all: create_static

create_static: create_obj
	mkdir -p lib
	$(AR) lib/libcalc.a obj/*.o

obj/%.o: calc/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

create_obj: $(patsubst calc/%.c,obj/%.o,$(wildcard calc/*.c))

run: create_static
	$(CC) main.c -Icalc -Llib -lcalc -o test_static
	./test_static

clean:
	rm -rf obj lib test_static