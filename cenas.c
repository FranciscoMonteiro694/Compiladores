#include <stdio.h>
#include <stdlib.h>

int DFS(int i,int nVertices,int **matriz,int *visited,int target);
int main()
{
    int nVertices, source, target,i,j;
    int **matriz;
    int *visited;
    scanf("%d %d %d",&nVertices,&source,&target);
    /* Alocar matriz */
    matriz=(int**)malloc(sizeof(int*)*nVertices);
    visited=(int*)malloc(sizeof(int)*nVertices);
    for(i=0;i<nVertices;i++){
        matriz[i]=(int*)malloc(sizeof(int)*nVertices);
        visited[i]=-1;
    }

    /* Ler input */
    for(i=0;i<nVertices;i++){
        for(j=0;j<nVertices;j++){
            scanf("%d",&matriz[i][j]);
        }
    }

    if(DFS(source-1,nVertices,matriz,visited,target-1)==1){
        printf("True\n");
    }
    else{
        printf("False\n");
    }


    return 0;
}

int DFS(int i,int nVertices,int **matriz,int *visited,int target)
{
    int j;
    visited[i]=1;
    /* Se chegou ao target */
    if(i==target){
        return 1;
    }
    for(j=0;j<nVertices;j++){
        if(visited[j]!=-1 && matriz[i][j]==1){
            DFS(i,nVertices,matriz,visited,target);
        }
    }
    return 0;
}
