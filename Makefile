exec = loop.out
sources = $(wildcard app/*.c)
objects = $(sources:.c=.o)
flags = -g


$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c super/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	cp ./loop.out /usr/local/bin/loop

clean:
	-chmod 777 app/*.o
	-chmod 777 *.out
	-rm *.out
	-rm *.o
	-rm app/*.o

build:
	-chmod 777 app/*.o
	-chmod 777 *.out
	-rm *.out
	-rm *.o
	-rm app/*.o

	make
	cp ./loop.out /usr/local/bin/loop