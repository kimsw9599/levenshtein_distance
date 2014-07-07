#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INSERT	 	0
#define DELETE	 	1
#define REPLACE	 	2
#define NO_CHANGE	3

#define NUM_EDIT_LIST	500

int minimum(int ins, int del, int rep, int *op)
{
	int min = -1;
	if(ins < del)
	{
		if(rep < ins){
			min = rep;
			*op=REPLACE;
		}
		else{
			min = ins;
			*op=INSERT;
		}
	}
	else
	{
		if(rep < del){
			min = rep;
			*op=REPLACE;
		}
		else{
			min = del;
			*op=DELETE;
		}
	}

	return min;
}

int main(void)
{
	char *x="revgniaton";
	char *y="recognition";
	int scost=0;

	int c=(int)strlen((const char*)x);
	int r=(int)strlen((const char*)y);

	printf("%s length : %d\n", x, c);
	printf("%s length : %d\n", y, r);

	int **distance=NULL;
	int **action=NULL;
	int edit_list[NUM_EDIT_LIST];	
	int edit_list_num=0;
	int d;

	for(int el=0; el<NUM_EDIT_LIST; el++) edit_list[el]=0;

	distance=(int **)malloc((r+1)*sizeof(int *));
	action=(int **)malloc((r+1)*sizeof(int *));
	for(int i=0; i <= r; i ++)
	{
		distance[i]=(int *)malloc((c+1)*sizeof(int));
		action[i]=(int *)malloc((c+1)*sizeof(int));
	}

	for(int i=0; i<= r; i ++)
	{
		for(int j=0; j <=c; j++)
		{
			distance[i][j]=0;
		}
	}

	for(int i=0; i <=c; i++) 
		distance[0][i]=i;

	for(int j=0; j <=r; j++) 
		distance[j][0]=j;

	for(int j=1; j <= r; j++)
	{
		for(int i=1;i <= c; i++)
		{
			if(x[i-1]==y[j-1])
				scost = 0;
			else
				scost = 1;

			int op;
			distance[j][i]=minimum(distance[j-1][i]+1, distance[j][i-1]+1, distance[j-1][i-1]+scost, &op);
			
			if(op==REPLACE && scost==0) 
				op=NO_CHANGE;

			action[j][i]=op;
		}
	}

	// print distance matrix
	for(int j=0; j <= r; j++)
	{
		for(int i=0;i <= c; i++)
		{
			printf("%2d ", distance[j][i]);
		}

		printf("\n");
	}

	d=distance[r][c];
	int j=r;
	int i=c;
	edit_list_num=0;
	do{
		if(action[j][i]==INSERT){
			edit_list[edit_list_num]=action[j][i];
			// printf("INSERT, %d\n", edit_list[edit_list_num]);
			j--;
		}
		else if(action[j][i]==DELETE){
			edit_list[edit_list_num]=action[j][i];
			// printf("DELETE, %d\n", edit_list[edit_list_num]);
			i--;
		}
		else if(action[j][i]==REPLACE){
			edit_list[edit_list_num]=action[j][i];
			// printf("REPLACE, %d\n", edit_list[edit_list_num]);
			i--;
			j--;
		}
		else if(action[j][i]==NO_CHANGE){
			edit_list[edit_list_num]=action[j][i];
			// printf("NO_CHANGE, %d\n", edit_list[edit_list_num]);
			i--;
			j--;
		}
		edit_list_num++;
	}while(!(j==0 && i==0));

	for(int idx=edit_list_num-1; idx >= 0; idx--){
		if(edit_list[idx]==INSERT){
			printf("INSERT\n");
		}else if(edit_list[idx]==DELETE){
			printf("DELETE\n");
		}else if(edit_list[idx]==REPLACE){
			printf("REPLACE\n");
		}else if(edit_list[idx]==NO_CHANGE){
			printf("NO CHANGE\n");
		}
	}


	for(int i=0; i <= r; i ++)
		free(distance[i]);
	free(distance);

	for(int i=0; i <= r; i ++)
		free(action[i]);
	free(action);
}