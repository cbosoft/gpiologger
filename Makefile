default: mtl


## Settings

COMPILER = gcc -Wall -O2
DRL = drl.c
MTL = mtl.c
DEBUG = -DDEBUG
OUT = gpiologger


## Recipes

drl:
	$(COMPILER) $(DRL) -o $(OUT)

drl-debug:
	$(COMPILER) $(DEBUG) $(DRL) -o $(OUT)

mtl:
	$(COMPILER) $(MTL) -o $(OUT)

mtl-debug:
	$(COMPILER) $(DEBUG) $(MTL) -o $(OUT)
