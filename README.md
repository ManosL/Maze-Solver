# Maze-Solver
A maze(aka labyrinth) solver with the use of a Queue.

# Introduction

	This program is a labyrinth solver with use of Queue.
The basic concept of this program is that when I am in a box
of the labyrinth the "neighbor" boxes that I don't visited I 
insert them in the queue. When a box is getting out of the queue
if I don't visited it and it has other neighbors I put it in another list.
If the box is useless I go on that list and I find the neighbors of 
this box. If the neighbor doesn't have another useful box I made the
same recursively and I delete that box. If queue is empty and I don't
reached the end labyrinth does not have a solution else I go to the
"final" list and I "filter" the nodes which lead me to the solution.
The "filter" method is explained at the code. And after that I print
the final path.

# Manual
	To compile it write on the terminal the command make.
To run it write on the terminal the command ./labyrinth_solver.
To clean the object files and the executable write on the terminal
the command make clean.

This program support labyrinths size of 21x21 included the external
walls. Start must be on the upper left corner and end must be on the
bottom right corner like the example labyrinth in labyrinth.txt.The
program reads the labyrinth from a text file(labyrinth.txt) so if 
you want to change the labyrinth you must have # as walls and spaces
(' ') as a free box. If you want to change lengthand width of the 
labyrinth open labyrinth.h and change length and width.


Creator: Manolis Lykos(Github Username: ManosL)
For any bugs contact me: manolislykos97@hotmail.gr
