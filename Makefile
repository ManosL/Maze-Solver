
labyrinth_solver: main.o labyrinth.o Path_element.o Queue.o Queue_Elem.o
	gcc main.o labyrinth.o Path_element.o Queue.o Queue_Elem.o -g -o labyrinth_solver

main.o:	main.c
	gcc -c main.c

labyrinth.o: labyrinth.c
	gcc -c labyrinth.c

Path_element.o: Path_element.c
	gcc -c Path_element.c

Queue.o: Queue.c
	gcc -c Queue.c

Queue_Elem.o: Queue_Elem.c
	gcc -c Queue_Elem.c

.PHONY: clean

clean:
	rm -f main.o labyrinth.o Path_element.o Queue.o Queue_Elem.o labyrinth_solver
