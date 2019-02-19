default: crl


## Settings

COMPILER = gcc -Wall -O2
CRL = crl.c
MTL = mtl.c
DEBUG = -DDEBUG
VERBOSE = -DVERBOSE
OUT = gpiologger

.PHONY: crl crl-debug mtl mtl-debug clean
## Recipes

crl:
	$(COMPILER) $(CRL) -o $(OUT)

crl-verbose:
	$(COMPILER) $(VERBOSE) $(CRL) -o $(OUT)

crl-debug:
	$(COMPILER) $(DEBUG) $(CRL) -o $(OUT)

mtl:
	$(COMPILER) $(MTL) -o $(OUT)

mtl-debug:
	$(COMPILER) $(DEBUG) $(MTL) -o $(OUT)
