default: fast

fast:
	gcc -Wall -Ofast gpiologger.c -o gpiologger

slow:
	gcc -Wall gpiologger.c -o gpiologger

normal:
	gcc -Wall -O2 gpiologger.c -o gpiologger
