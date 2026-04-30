all:
	gcc src/main.c -o noxide

install:
	make
	sudo cp ./noxide /usr/local/bin/
