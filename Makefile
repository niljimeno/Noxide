all:
	gcc src/main.c -o noxide

test:
	make
	./noxide add /caca
	./noxide read
