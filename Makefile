CC=gcc
all:
	$(CC) dumpbar.c -o dumpbar
	$(CC) reado01.c -o reado01
	$(CC) dumpmif.c -o dumpmif
	$(CC) mifcrypt.c -o mifcrypt
	$(CC) dumpsig.c -o dumpsig
	$(CC) brew_file.c -o brew_file
	$(CC) o01create.c -o o01create
install:
	mkdir /opt/brew_utils
	cp ./dumpbar /opt/brew_utils
	cp ./dumpmif /opt/brew_utils
	cp ./reado01 /opt/brew_utils
	cp ./mifcrypt /opt/brew_utils
	cp ./brew_file /opt/brew_utils
	cp ./o01create /opt/brew_utils
	ln -s /opt/brew_utils/dumpbar /bin/dumpbar
	ln -s /opt/brew_utils/dumpmif /bin/dumpmif
	ln -s /opt/brew_utils/reado01 /bin/reado01
	ln -s /opt/brew_utils/mifcrypt /bin/mifcrypt
	ln -s /opt/brew_utils/brew_file /bin/brew_file
	ln -s /opt/brew_utils/o01create /bin/o01create
	echo Done
uninstall:
	- rm /bin/dumpbar
	- rm /bin/dumpmif
	- rm /bin/reado01
	- rm /bin/mifcrypt
	- rm /bin/brew_file
	- rm /bin/o01create
	- rm -r /opt/brew_utils/
	echo Done
