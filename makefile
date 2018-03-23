all:	prog1generator prog1sorter

prog1generator:	prog1generator.o parsers.o
				gcc -o prog1generator prog1generator.o parsers.o
				
prog1generator.o:	prog1generator.c
					gcc -Wall -c prog1generator.c

prog1sorter:	prog1sorter.o parsers.o
				gcc -o prog1sorter prog1sorter.o parsers.o
				
prog1sorter.o:	prog1sorter.c
				gcc -Wall -c prog1sorter.c

parsers.o:	parsers.c
			gcc -Wall -c parsers.c
			
clean:
		rm -f *.o prog1sorter prog1generator parsers
			

