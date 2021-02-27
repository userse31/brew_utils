CC=gcc
all:
	$(CC) dumpbar.c -o dumpbar
	$(CC) reado01.c -o reado01
	$(CC) dumpmif.c -o dumpmif
	$(CC) mifcrypt.c -o mifcrypt
install:
	mkdir /opt/brew_utils
	cp ./dumpbar /opt/brew_utils
	cp ./dumpmif /opt/brew_utils
	cp ./reado01 /opt/brew_utils
	cp ./mifcrypt /opt/brew_utils
	ln -s /opt/brew_utils/dumpbar /bin/dumpbar
	ln -s /opt/brew_utils/dumpmif /bin/dumpmif
	ln -s /opt/brew_utils/reado01 /bin/reado01
	ln -s /opt/brew_utils/mifcrypt /bin/mifcrypt
	echo Done
uninstall:
	rm /bin/dumpbar
	rm /bin/dumpmif
	rm /bin/reado01
	rm /bin/mifcrypt
	rm -r /opt/brew_utils/
	echo Done
