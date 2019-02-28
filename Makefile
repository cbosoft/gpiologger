default: crl

COMPILER = gcc -Wall -Wextra -pedantic -O2
CRL = crl.c
DEBUG = -DDEBUG
VERBOSE = -DVERBOSE
OUT = gpiologger

crl: crl.c
	$(COMPILER) $(CRL) -o $(OUT)

crl-verbose: crl.c
	$(COMPILER) $(VERBOSE) $(CRL) -o $(OUT)

crl-debug: crl.c
	$(COMPILER) $(DEBUG) $(CRL) -o $(OUT)
