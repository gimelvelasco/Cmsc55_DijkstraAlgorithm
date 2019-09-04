/*
////////////////////////Dijkstra's Algorithm for UNDIRECTED graphs////////////////////////////////////
This code only accepts edges that has no more than 4 digits
The size of the adjacency matrix can be changed by manipulating the value of DIM below.
A Matrix of size nxn where n is 2 to 26 can only be handled by this code.
There is little to no error handling implemented in this code.
This code is based on how Dijkstra's Algorithm is explained in https://www.youtube.com/watch?v=5GT5hYzjNoo
coded by Gi111PH
2012-58922 VELASCO, Gimel David F.
11.30.15
*/
/////////////////////////////////////
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#define DIM 8

int main (){
	///////////////////////////INITIALIZING SECTION
	int i,j,n,k,cV,cVprev,cVtemp,min,minDist,allVisited;	
	char alphabet[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','-'};//name of vertices
	int aMatrix[DIM][DIM]; //adjacency matrix
	int pathDist[DIM][DIM];//holds the path distance from A to every other vertex
	int pathOrig[DIM][DIM];//holds the vertex origin of the corresponding edge weight in pathDist
	int pathChar[DIM][DIM];//holds the path from A to every other vertex
	int visitedTT[DIM];//holds the visited vertices by using a binary array
	for(i=0;i<DIM;i++){
		for(j=0;j<DIM;j++){
			aMatrix[i][j] = 0;
			pathDist[i][j] = 9999; //sets the initial distance of A to every other vertex to infinity (9999 in this case)
			pathOrig[i][j] = 9999; //holds the vertex origin of each corresponding edge weight in pathDist. the diagonal is the only one needed to get the path
			pathChar[i][j] = 27;
		}
		visitedTT[i] = 0;
	}/////////////////////////PARSING Initialization
	FILE *strm = NULL;
	char cchar;
	char tempString[5]; //accepts only 4 digits max
	strm = fopen("aMatrix.csv","r");
	/////////////////////////
	if(strm==NULL){
		printf("File not found.\n");
		usleep(500000);
		printf("Program Terminated.");
		return 0;
	}
	else{
		/////////////////////////////PARSING Section/////////////////////
		for(i=0;i<DIM;i++){
			for(j=0;j<DIM;j++){
				n=0;
				do{
					cchar = fgetc(strm);
					tempString[n] = cchar;
					n++;
					if(cchar == '\n' || cchar == EOF){//prevents the... uhmmm yeah xD
						break;
					}
				}while(cchar!=',');
				tempString[n-1] = '\0';
				sscanf(tempString,"%d",&aMatrix[i][j]);
			}
		}
		fclose(strm);
		//////////////////////////////MAIN Algorithm/////////////////////
		for(i=0;i<DIM;i++){
			for(j=0;j<DIM;j++){
				if(aMatrix[i][j] == 0){
					aMatrix[i][j] = 9999; //in this code I used the interpreted 9999 as edges that are not adjacent (infiniti)
				}
			}
		}
		cV = 0; //current Vertex
		cVprev = 0;
		pathDist[cV][0] = 0; //A to A distance is zero;
		visitedTT[cV] = 1;
		do{
			for(i=0;i<DIM;i++){//updates the pathDist
				if(cV==i || visitedTT[i]){
					//ignore
				}
				else{
					if(cV==0){//update for the first step
						pathDist[cV][i] = aMatrix[cV][i];
						pathOrig[cV][i] = cV;
					}
					else if(aMatrix[cV][i] + pathDist[cV][cV] < pathDist[cVprev][i]){//update
						pathDist[cV][i] = aMatrix[cV][i] + pathDist[cV][cV];
						pathOrig[cV][i] = cV;
					}
					else{//retain
						pathDist[cV][i] = pathDist[cVprev][i];
						pathOrig[cV][i] = cVprev;
					}
				}
				if(cV==0){//update for the first step
					pathOrig[cV][i] = cV;
				}
				else if(aMatrix[cV][i] + pathDist[cV][cV] < pathDist[cVprev][i]){//update
					pathOrig[cV][i] = cV;
				}
				else{//retain
					pathOrig[cV][i] = pathOrig[cVprev][i];
				}
			}
			minDist = 9999;
			for(i=0;i<DIM;i++){//moves on to the unvisited vertex with least connecting edge weight
				if((pathDist[cV][i] < minDist) && (visitedTT[i] == 0)){ //if smaller and unvisited
					minDist = pathDist[cV][i];
					cVtemp = i;
				}
			}
			cVprev = cV;
			cV = cVtemp;
			pathDist[cV][cV] = pathDist[cVprev][cV];//updates the visited vertex
			visitedTT[cV] = 1;
			for(i=0;i<DIM;i++){//checks if all the vertices are already visited
				if(visitedTT[i] == 0){
					allVisited = 0;
					break;
				}
				else{
					allVisited = 1;
				}
			}
		}while(allVisited == 0);
		pathOrig[cV][DIM-1] = pathOrig[cVprev][DIM-1];
		for(i=0;i<DIM;i++){//plots the path from A to every other vertex
			j=0;
			k=i;
			pathChar[i][j] = i;
			j++;
			while(pathChar[i][j-1] != 0){
				
				pathChar[i][j] = pathOrig[k][k];
				k = pathOrig[k][k];
				j++;
			}
		}
		for(i=0;i<DIM;i++){
			for(j=0;j<DIM;j++){
				if(aMatrix[i][j] == 9999){
					aMatrix[i][j] = 0; //resets the infinite value to 0 for printing purposes
				}
			}
		}
		///////////////////////PRINTING Section//////////////////
		usleep(500000);
		printf("\n\n\nAdjacency Matrix\n  ");
		usleep(200000);
		for(i=0;i<DIM;i++){
			printf("| %c  ",alphabet[i]);
			usleep(50000);
		}
		printf("\n");
		for(i=0;i<DIM;i++){
			printf(" %c|",alphabet[i]);
			for(j=0;j<DIM;j++){
				if(aMatrix[i][j] < 10){//if 1-digit
					printf("  %d ",aMatrix[i][j]);
				}
				else if(aMatrix[i][j] < 100){//if 2-digit
					printf(" %d ",aMatrix[i][j]);
				}
				else if(aMatrix[i][j] < 1000){//if 3-digit
					printf(" %d",aMatrix[i][j]);
				}
				else{//if 4-digit
					printf("%d",aMatrix[i][j]);
				}
				if(j==DIM-1){
					printf("\n");
				}
				else{
					printf("|");
				}
				usleep(50000);
			}
		}
		usleep(500000);
		printf("\nImplementing Dijkstra's Algorithm,\nShortest Paths:\n    |Dist|Path\n");
		usleep(200000);
		for(i=0;i<DIM;i++){
			printf(" A-%c|",alphabet[i]);
			usleep(50000);
			if(pathDist[i][i] < 10){//if 1-digit
				printf("  %d |",pathDist[i][i]);
			}
			else if(pathDist[i][i] < 100){//if 2-digit
				printf(" %d |",pathDist[i][i]);
			}
			else if(pathDist[i][i] < 1000){//if 3-digit
				printf(" %d|",pathDist[i][i]);
			}
			else{//if 4-digit
				printf("%d|",pathDist[i][i]);
			}
			usleep(50000);
			for(j=0;j<DIM;j++){
				if(pathChar[i][DIM-1-j] == 27){
					
				}
				else{
					if(DIM-1-j == 0){
						printf("%c",alphabet[pathChar[i][DIM-1-j]]);
					}
					else{
						printf("%c-",alphabet[pathChar[i][DIM-1-j]]);
					}
					usleep(50000);
				}
			}
			printf("\n");
			usleep(50000);
		}
		printf("\n");
		usleep(50000);
	}
	usleep(999999);
	return 0;
}