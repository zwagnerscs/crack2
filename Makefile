# -*- indent-tabs-mode:t; -*-

CC=clang
CFLAGS=-g
NUM_HASHES=20
ROCKYOU=rockyou100.txt

all: hashpass crack

# This rule links hashpass.o and md5.o along with the
# libssl and libcrypto libraries to make the executable.
hashpass: hashpass.o md5.o
	$(CC) hashpass.o md5.o -o hashpass -l crypto

md5.o: md5.c md5.h
	$(CC) $(CFLAGS) -c md5.c -Wall

hashpass.o: hashpass.c md5.h
	$(CC) $(CFLAGS) -c hashpass.c -Wall

# Add a recipe to build crack out of crack.o and md5.o.
# See the rule for hashpass above.
# Remove the "@echo" lines.
crack: crack.o md5.o
	@echo No rule for building the executable.
	@echo "  Modify the Makefile first."


# Add a recipe to build crack.o out of crack.c
# Remove the "@echo" lines.
crack.o: crack.c md5.h
	@echo No rule for building crack.o
	@echo "  Modify the Makefile first"


hashes: hashpass
	shuf -n $(NUM_HASHES) $(ROCKYOU) > passwords.txt
	./hashpass < passwords.txt > hashes.txt

hashes.txt: hashes

clean:
	rm -f *.o hashpass crack hashes.txt passwords.txt

test: crack hashes.txt
	./crack hashes.txt $(ROCKYOU)

check: crack hashes.txt
	valgrind ./crack hashes.txt $(ROCKYOU)
