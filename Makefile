# -*- indent-tabs-mode:t; -*-

CC=clang
NUM_HASHES=20
ROCKYOU=rockyou100.txt

all: hashpass crack

# This rule links hashpass.o and md5.o along with the
# libssl and libcrypto libraries to make the executable.
hashpass: hashpass.o md5.o
	clang hashpass.o md5.o -o hashpass -l ssl -l crypto

md5.o: md5.c md5.h
	clang -g -c md5.c -Wall

hashpass.o: hashpass.c md5.h
	clang -g -c hashpass.c -Wall

# Add a recipe to build crack out of crack.o and md5.o.
# See the rule for hashpass above.
crack: crack.o md5.o


# Add a recipe to build crack.o out of crack.c
crack.o: crack.c md5.h


hashes: hashpass
	shuf -n $(NUM_HASHES) $(ROCKYOU) > passwords.txt
	./hashpass < passwords.txt > hashes.txt

clean:
	rm -f *.o hashpass crack hashes.txt passwords.txt

test: crack
	./crack hashes.txt $(ROCKYOU)
