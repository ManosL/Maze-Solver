/*Path element is the box of the labyrinth that leads to the exit of the labyrinth*/

#include <stdio.h>
#include <stdlib.h>

#include "Path_element.h"
#include "labyrinth.h"

struct Path_element{
	int row,column,move;
	int useful_neighbors; /*Just the number of neighbors*/
	Path_elementPtr next;
};

void PathElement_Create(Path_elementPtr* list){
	*list = NULL;
}

int PathElement_Empty(Path_elementPtr list){
	return list == NULL;
}

int PathElement_Search(Path_elementPtr list,int row,int column){
	Path_elementPtr current;

	current = list;

	while(current != NULL){
		if(current->row == row && current->column == column){
			return 1;
		}

		current = current->next;
	}

	return 0;
}

void PathElement_Insert(Path_elementPtr* list,int row,int col,int move,int neighbors){
	Path_elementPtr temp,last;

	if(PathElement_Empty(*list)){
		*list = malloc(sizeof(struct Path_element));
		(*list)->next = NULL;
		(*list)->row = row;
		(*list)->column = col;
		(*list)->move = move;
		(*list)->useful_neighbors = neighbors; 
	}
	else{
		temp = *list;
		while(temp != NULL){
			last = temp;
			temp = temp->next;
		}

		last->next = malloc(sizeof(struct Path_element));
		last = last->next;

		last->row = row;
		last->column = col;
		last->move = move;
		last->useful_neighbors = neighbors;
		last->next = NULL;
	}
}

void PathElement_SearchNeighbor(Path_elementPtr* list,int row,int col){ /*finds the neighbors of a useless box*/
	Path_elementPtr current;

	current = *list;             /*I traverse the list*/
	while(current != NULL){
		if(current->row - 1 == row && current->column == col){ /*check if current box is neighbor of the useless box*/
			current->useful_neighbors--;                       /*If it is I decrease the number of the useful neighbors*/
			if(current->useful_neighbors == 1){                /*If I don't have any useful neighbors(is ==1 because the one neighbors who*/
				PathElement_SearchNeighbor(list,row+1,col);    /*remains I already visited him and it covers me when current found neighbor*/
				current = current->next;					   /*in another recursive call) I found the neighbors of current with recursion*/
				PathElement_Delete(list,row+1,col);			   /*Current is the next node because I will delete the previous node*/
			}
			else 											  /*Else I will just go to the next node*/
				current = current->next;
		}
		else
		if(current->row == row && current->column - 1 == col){ /*Likewise, the other cases*/
			current->useful_neighbors--;
			if(current->useful_neighbors == 1){
				PathElement_SearchNeighbor(list,row,col+1);
				current = current->next;
				PathElement_Delete(list,row,col+1);
			}
			else
				current = current->next;
		}
		else
		if(current->row + 1 == row && current->column == col){
			current->useful_neighbors--;
			if(current->useful_neighbors == 1){
				PathElement_SearchNeighbor(list,row-1,col);
				current = current->next;
				PathElement_Delete(list,row-1,col);
			}
			else
				current = current->next;
		}
		else
		if(current->row == row && current->column + 1 == col){
			current->useful_neighbors--;
			if(current->useful_neighbors == 1){
				PathElement_SearchNeighbor(list,row,col-1);
				current = current->next;
				PathElement_Delete(list,row,col-1);
			}
			else
				current = current->next;
		}
		else
			current = current->next;
	}
}

void PathElement_Delete(Path_elementPtr* list,int row,int col){ /*Just a search and delete node function*/
	Path_elementPtr current,previous,temp; /*current = node to be deleted previous = previous node of current*/

	current = *list;
	while(current != NULL){
		if(current->row == row && current->column == col){
			break;
		}
		else{
			current = current->next;
		}
	}

	if(current == NULL){
		printf("%d %d\n",row,col);
		printf("I didn't found that node\n");
		return;
	}

	if(current == *list){ /*if node to be deleted is the first node*/
		*list = current->next;
		free(current);
		return ;
	}
	else{
		temp = *list;
		while(temp != current){
			previous = temp;
			temp = temp->next;
		}

		previous->next = current->next;
		free(current);
		return ;
	}
}

void PathElement_FinalPath(Path_elementPtr* list,int** labyrinth){ /*This function has 2 parts*/
	int current_move=0,previous_step_row,previous_step_col;		   /*1st part = finding the neighbors on each node of the list*/
	Path_elementPtr current,temp,temp2;							   /*from current move to next move and if the current does not*/
																   /*have neighbors on the next move the node will be deleted*/
	/*Setting up the useful neighbors of each node*/				/*Before I search for neighbor on previous moves*/

	current = *list;												/*2nd part = I just print the final path*/
	while(current != NULL){
		current->useful_neighbors = 1;
		current = current->next;
	}

	current = *list;
	while(current != NULL){
		temp = current;

		while(temp->move != current->move + 2){
			if(temp == NULL) break;

			if(temp->move == current->move){
				/*printf("%d %d\n",temp->move,current->move); testing*/
				temp = temp->next;
				if(temp == NULL) break;
			}
			else
				if(temp->move == current->move+1){
					if((current->row -1) == temp->row && (current->column) == temp->column){
						current->useful_neighbors++;
					}

					if((current->row) == temp->row && (current->column - 1) == temp->column){
						current->useful_neighbors++;
					}

					if((current->row + 1) == temp->row && (current->column) == temp->column){
						current->useful_neighbors++;
					}

					if((current->row) == temp->row && (current->column + 1) == temp->column){
						current->useful_neighbors++;
					}

					temp = temp->next;
					if(temp == NULL) break;

				}
			
		}

		if(current->row == length - 2 && current->column == width -1){  /*If I reach to the final of the labyrnth*/
			break;
		}
		else
		if(current->useful_neighbors == 1){
			temp2 = current;
			/*printf("DEL %d %d\n",temp2->row,temp2->column);  testing */
 			current = current->next;
			PathElement_FinalPathNeighbor(list,temp2->row,temp2->column,temp2->move);
			PathElement_Delete(list,temp2->row,temp2->column);
		}
		else
			current = current->next;

	}

	printf("Full path is:\n");
	current = *list;
	while(current != NULL){
		if(current->move == current_move){     /*I write that because I want to be sure that I don't have any confliting paths*/
			printf("%d %d\n",current->row,current->column); 
			labyrinth[current->row][current->column] = '.' ;
			current_move++;
			current = current->next;
		}
		else
			current = current->next;
	}

	return ;
}

void PathElement_FinalPathNeighbor(Path_elementPtr* list,int row,int col,int move){ /*similar as PathElement_SearchNeighbor*/
	Path_elementPtr current,temp2;

	current = *list;
	while(current->move < move && current != NULL){  /*With only difference that I search till the current->move is smaller than move*/ 
		if(current->row - 1 == row && current->column == col){
			current->useful_neighbors--;
			if(current->useful_neighbors == 1){
				PathElement_FinalPathNeighbor(list,row+1,col,current->move);
				current = current->next;
				PathElement_Delete(list,row+1,col);
			}
			else
				current = current->next;
		}
		else
		if(current->row == row && current->column - 1 == col){
			current->useful_neighbors--;
			if(current->useful_neighbors == 1){
				PathElement_FinalPathNeighbor(list,row,col+1,current->move);
				current = current->next;
				PathElement_Delete(list,row,col+1);
			}
			else
				current = current->next;
		}
		else
		if(current->row + 1 == row && current->column == col){
			current->useful_neighbors--;
			if(current->useful_neighbors == 1){
				PathElement_FinalPathNeighbor(list,row-1,col,current->move);
				current = current->next;
				PathElement_Delete(list,row-1,col);
			}
			else
				current = current->next;
		}
		else
		if(current->row == row && current->column + 1 == col){
			current->useful_neighbors--;
			if(current->useful_neighbors == 1){
				PathElement_FinalPathNeighbor(list,row,col-1,current->move);
				current = current->next;
				PathElement_Delete(list,row,col-1);
			}
			else
				current = current->next;
		}
		else
			current = current->next;

	}
}

void PathElement_ListDestroy(Path_elementPtr list){

	if(list != NULL){
		PathElement_ListDestroy(list->next);
		free(list);
	}
}
