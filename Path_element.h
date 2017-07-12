#ifndef __PATH__
#define __PATH__

typedef struct Path_element* Path_elementPtr;

void PathElement_Create(Path_elementPtr*);
int PathElement_Empty(Path_elementPtr);
int PathElement_Search(Path_elementPtr,int,int);
void PathElement_Insert(Path_elementPtr*,int,int,int,int);
void PathElement_SearchNeighbor(Path_elementPtr*,int,int);
void PathElement_Delete(Path_elementPtr*,int,int);
void PathElement_FinalPath(Path_elementPtr*,int**);
void PathElement_ListDestroy(Path_elementPtr);
void PathElement_FinalPathNeighbor(Path_elementPtr*,int,int,int);

#endif