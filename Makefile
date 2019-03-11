default: crl

COMPILER = gcc -Wall -Wextra -pedantic -O2
DEBUG = -DDEBUG -DVERBOSE
VERBOSE = -DVERBOSE
OUT = gpiologger

crl: crl.c
	$(COMPILER) crl.c -o $(OUT)

crl-verbose: crl.c
	$(COMPILER) $(VERBOSE) crl.c -o $(OUT)

crl-debug: crl.c
	$(COMPILER) $(DEBUG) crl.c -o $(OUT)

srl: srl.c
	$(COMPILER) srl.c -o $(OUT)

srl-verbose: srl.c
	$(COMPILER) $(VERBOSE) srl.c -o $(OUT)

srl-debug: srl.c
	$(COMPILER) $(DEBUG) srl.c -o $(OUT)
