#include <stdio.h>
#include "labyrinth.h"

void labyrinth_setup(FILE* file,int** labyrinth){
	int i,j;
	int character;

	/*start: row = 1 column = 0;
	  end: row = length-2 column = width-1*/

	/*Via file*/

	for(i=0;i<length;i++){
		for(j=0;j<width;j++){
			character = getc(file);
			if(character == '\n'){
				j--;
			}
			else
				labyrinth[i][j] = character;
		}
	}

	/*If I want to set up the labyrinth via scanf*/
	//labyrinth[1][0] = ' ';
	//labyrinth[length-2][width-1] = ' ';

	/*Setting up the labyrinth*/

	
	/*for(i=0;i<width;i++){
		labyrinth[0][i] = '#';
	}

	for(i=2;i<length;i++){
		labyrinth[i][0] = '#';
	}

	for(i=1;i<length;i++){
		if(i!=length-2)
		labyrinth[i][width-1] = '#';
	}

	for(i=0;i<width-1;i++){
		labyrinth[length-1][i] = '#';
	}
	
	for(i=1;i<length-1;i++){
		for(j=1;j<width-1;j++){
			printf("Give #(35) or Space(32):");
			scanf("%d",&labyrinth[i][j]);
			printf("\n");
		}
	}*/

}

void labyrinth_print(int** labyrinth){
	int i,j;

	
	for(i=0;i<length;i++){
		for(j=0;j<width;j++){
			printf("%c",labyrinth[i][j]);
		}
		printf("\n");
	}	
}