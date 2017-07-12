#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Queue.h"
#include "labyrinth.h"
#include "Path_element.h"


int main(void){
	FILE* labyrinth_file = fopen("labyrinth.txt","r");
	QueuePtr Queue;
	Path_elementPtr full_path;
	int** labyrinth;
	int i,j;	
	int curr_row,curr_col,curr_move;
	int useful_neighbors=0;

	labyrinth = malloc(length*sizeof(int*));
	if(labyrinth == NULL){
		printf("Memory Error\n");
		return -1;
	}

	for(i=0;i<length;i++){
		labyrinth[i] = malloc(width*sizeof(int));
		if(labyrinth[i] == NULL){
			printf("Memory Error\n");
			return -1;
		}
	}

	labyrinth_setup(labyrinth_file,labyrinth);

	printf("Your labyrinth is:\n");

	labyrinth_print(labyrinth);

	Queue = Queue_Create();
	Queue_Insert(Queue,1,0,0);

	PathElement_Create(&full_path);


	while(!Queue_Empty(Queue)){
		Queue_Delete(Queue,&curr_row,&curr_col,&curr_move);

		if(curr_row == 1 && curr_col == 0){
			assert(curr_move == 0);
			PathElement_Insert(&full_path,curr_row,curr_col,curr_move,1);
			Queue_Insert(Queue,curr_row,curr_col+1,curr_move+1);
			useful_neighbors = 0;
		}
		else
		if(curr_row == length -2 && curr_col == width-1){  /*I reached to the end*/
			PathElement_Insert(&full_path,curr_row,curr_col,curr_move,useful_neighbors);
			PathElement_FinalPath(&full_path,labyrinth);
			Queue_Destroy(&Queue);

			PathElement_ListDestroy(full_path);

			printf("The solution is\n");
			labyrinth_print(labyrinth);

			for(i=0;i<length;i++){
				free(labyrinth[i]);
			}

			free(labyrinth);
			fclose(labyrinth_file);
			return 0 ;
		}
		else
		if(!PathElement_Search(full_path,curr_row,curr_col)){

			if(labyrinth[curr_row+1][curr_col] != '#'){
				if(!Queue_Search(Queue,curr_row+1,curr_col) && !PathElement_Search(full_path,curr_row+1,curr_col)){
					Queue_Insert(Queue,curr_row+1,curr_col,curr_move+1);
				}
				useful_neighbors++;
			}

			if(labyrinth[curr_row][curr_col+1] != '#'){
				if(!Queue_Search(Queue,curr_row,curr_col+1) && !PathElement_Search(full_path,curr_row,curr_col+1)){
					Queue_Insert(Queue,curr_row,curr_col+1,curr_move+1);
				}

				useful_neighbors++;
			}


			if(labyrinth[curr_row][curr_col-1] != '#'){
				if(!Queue_Search(Queue,curr_row,curr_col-1) && !PathElement_Search(full_path,curr_row,curr_col-1) && curr_col-1>0){
					Queue_Insert(Queue,curr_row,curr_col-1,curr_move+1);
				}

				useful_neighbors++;
			}

			if(labyrinth[curr_row-1][curr_col] != '#'){
				if(!Queue_Search(Queue,curr_row-1,curr_col) && !PathElement_Search(full_path,curr_row-1,curr_col)){
					Queue_Insert(Queue,curr_row-1,curr_col,curr_move+1);
				}

				useful_neighbors++;
			}

			
			if(useful_neighbors == 1){
				PathElement_SearchNeighbor(&full_path,curr_row,curr_col);
			}
			else
				PathElement_Insert(&full_path,curr_row,curr_col,curr_move,useful_neighbors);

			/*printf("%d %d %d\n",curr_row,curr_col,curr_move); /*testing*/
			useful_neighbors = 0;
		}
	}

	printf("Labyrinth doesn't have a solution\n");
	Queue_Destroy(&Queue);
	PathElement_ListDestroy(full_path);
	for(i=0;i<length;i++){
		free(labyrinth[i]);
	}

	fclose(labyrinth_file);
	free(labyrinth);
	return 0;	
}