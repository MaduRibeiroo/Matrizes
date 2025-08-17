#include<stdio.h>
#define MAX 10

int  main()
{
	int mat[MAX][MAX],n,tam;
	char linha[25];
	FILE *ptr = fopen("teste.txt", "r");
	fgets(linha,100,ptr);
    linha[strcspn(linha,"\n")] = '\0'; // tira o \n
	
	if(strcmp(linha,"MA") == 0) // MATRIZ DE ADJACENCIA
	{
        fgets(linha,100,ptrArq); // lê a linha dos vértices (ex: "A B C D") ----
        linha[strcspn(linha,"\n")] = '\0';
        int i=0, j=0;
        while(linha[i]!='\0'){
            if(linha[i]!=' ' && linha[i]!='\n' && linha[i]!='\r'){
                n++;
                while(linha[i]!=' ' && linha[i]!='\0') // anda até o próximo espaço
					i++;
            }else{
                i++;
            }
        }
		//grafo ou diagrafo
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