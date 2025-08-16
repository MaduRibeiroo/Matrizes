#include<stdio.h>
#define MAX 10

int  main()
{
	int mat[MAX][MAX],n,tam;
	char linha[25];
	FILE *ptr = fopen("teste.txt", "r");
	fgets(linha,25,ptr);
	
	if(strcmp(linha,"MA") == 0) // MA
	{
		//////////grafo ou diagrafo
		int grafo=0; //achei 1, nao achei 0
		for(int lin=0, col=0;lin<tam && !grafo; lim++)
		{
			if(mat[lin][col] != mat[col][lin]) //digrafo
				grafo = 1;
		}
		for(int lin = tam-1, col=0; col<tam && !grafo; col++){
			if(mat[lin][col] != mat[col][lin]) //digrafo
				grafo = 1;
		}
		
		
		if(grafo == 0)
			printf("Esta matriz e um grafo!");
		else
			printf("Esta matriz e um digrafo!");
		
	}
	else {
		if(strcmp(linha,"MI") == 0){// MI
			int achei=0; //achei 1, nao achei 0
			for(int lin=0;lin<tam && !achei;lim++)
			{
				for(int col=0;col<tam && !achei;col++)
				{
					if(mat[lin][col] < 0)
						achei = 1;
				}
			}
		}
		else
		{
			
		}
	}
	
	
}
