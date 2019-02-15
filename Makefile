default: crl


## Settings

COMPILER = gcc -Wall -O2
CRL = crl.c
MTL = mtl.c
DEBUG = -DDEBUG
OUT = gpiologger


## Recipes

crl:
	$(COMPILER) $(CRL) -o $(OUT)

crl-debug:
	$(COMPILER) $(DEBUG) $(CRL) -o $(OUT)

mtl:
	$(COMPILER) $(MTL) -o $(OUT)

mtl-debug:
	$(COMPILER) $(DEBUG) $(MTL) -o $(OUT)
