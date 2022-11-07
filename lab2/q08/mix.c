#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int x=0, y=0, i=0, j=0, k=0, **m1, **m2;
	printf(" x, y : ");
	scanf("%d %d", &x, &y);
	
	m1 = (int **)malloc(sizeof(int *)*y);
	m2 = (int **)malloc(sizeof(int *)*y);
	
	
	for(i = 0; i<x; i++){
		m1[i] = (int *)malloc(sizeof(int)*y);
		m2[i] = (int *)malloc(sizeof(int)*y);
		}
	
	for(i = 0; i<x; i++){
		for( j = 0; j<y;j++){
		scanf("%d",&m1[i][j]);	
		}
	}
	for(i = 0; i<x; i++){
                for( j = 0; j<y;j++){
                scanf("%d",&m2[i][j]);
                }
        }

	printf("------------------------------\n");
	for(i = 0; i < x; i++){
		for(j = 0; j < y; j++){
			printf("%5d",m1[i][j]);	
		}printf("\n");
		}
	
	printf("------------------------------\n");
	for(i = 0; i < x; i++){
		for(j = 0; j < y; j++){
			printf("%5d",m2[i][j]);	
		}printf("\n");
	}
	printf("-------------------------------\n");
	for(i = 0; i < x; i++){
		for(j = 0; j < y; j++){
			printf("%5d",m1[i][j]+m2[i][j]);	
		}printf("\n");
	}
	return 0;
	
	free(m1);
	free(m2);
}
