CC=gcc
all:
	- mkdir bin
	$(CC) dumpbar.c -o ./bin/dumpbar
	$(CC) reado01.c -o ./bin/reado01
	$(CC) dumpmif.c -o ./bin/dumpmif
	$(CC) mifcrypt.c -o ./bin/mifcrypt
	$(CC) dumpsig.c -o ./bin/dumpsig
	$(CC) brew_file.c -o ./bin/brew_file
	$(CC) writeo01.c -o ./bin/writeo01
install:
	mkdir /opt/brew_utils
	cp -r ./bin/ /opt/brew_utils/
	echo Done
uninstall:
	- rm -r /opt/brew_utils/
	echo Done
clean:
	- rm -r ./bin/
