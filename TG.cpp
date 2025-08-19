#include <stdio.h>
#include <math.h>
#define MAX 10

strcut ListaADJ{
	char origem[2],destino[2];
	int valor;
	ListaADJ* prox;
}

ListaADJ* novaLista(char origem[2],char destino[2],int valor)
{
	ListaADJ* nova = new(ListaADJ); 
	strcpy(nova->origem,origem);
	strcpy(nova->destino,destino);
	nova->valor = valor;
	nova->prox=NULL;
	return nova;
}

void inserirFinalLista(ListaADJ &L,char origem[2],char destino[2],int valor)
{
	ListaADJ *aux,*nova = novaLista(origem,destino,valor);
	aux=L;
	if(L==NULL)
	{
		L=nova;
	}
	else
	{
		while(aux->prox!=NULL)
		{
			aux=aux->prox;
		}
		aux->prox=nova;
	}
}


int  main()
{
	int mat[MAX][MAX],tam=0;
	char linha[25];
	FILE *ptr = fopen("teste.txt", "r");
	fgets(linha,100,ptr);
    linha[strcspn(linha,"\n")] = '\0'; // tira o \n
	
	if(strcmp(linha,"MA") == 0) // MATRIZ DE ADJACENCIA
	{
        fgets(linha,100,ptrArq); // le a linha dos vertices (ex: "A B C D")
        linha[strcspn(linha,"\n")] = '\0';
        int i=0, j=0;
        while(linha[i]!='\0'){
            if(linha[i]!=' ' && linha[i]!='\n'){
                tam++;
                while(linha[i]!=' ' && linha[i]!='\0') // anda ate o proximo espaco
					i++;
            }
			else{
                i++;
            }
        }
		//grafo ou diagrafo
		int grafo=0; //achei 1, nao achei 0
		for(int lin=0, col=0;lin<tam && !grafo; lin++)
		{
			if(mat[lin][col] != mat[col][lin]) //digrafo
				grafo = 1;
		}
		for(int lin = tam-1, col=0; col<tam && !grafo; col++){
			if(mat[lin][col] != mat[col][lin]) //digrafo
				grafo = 1;
		}
		
		//simples (sem laco)
        int simples=0;  
        for(int lin=0;lin<tam && !simples;lin++){
            if(mat[lin][lin]!=0) 
				simples=1; // tem laco
        }

		// int regular=0; count; countAnt=0;
		// for(lin=0; lin<tam;lin++){
		// 	for(col=0, count=0; col<tam;col++){
		// 		if(mat[lin][col] != 0)
		// 			count += 1;
		// 	}
		// 	if(lin > 0 && countAnt != count)
		// 		regular=1;
		// 	countAnt = count;
		// }
		

		//Regular
		int grau=0,atual=0,tl=0,regular=0;
		for(int lin=0; lin < tam  && !regular; lin++ ){
			atual=0
			for(int col =0;col < tam && !regular ; col++)
			{
				if(lin==0)
				{
					grau+=mat[lin][col];
				}
				else{
					atual+=mat[lin][col];
				}
			}
			if(grau!=atual)
			regular=1;
			
		}
		
		for(int col=0;col < tam && !regular; col++)
			atual=0;
			for(int lin=0; lin < tam && !regular; lin++ ){
			{
				if(lin==0)
				{
					atual+=mat[lin][col];
				}
			}
			if(atual!=grau)
				regular=1;
		}


		//completo
		int cont=0,completo=0;
		for(int lin=0,col=0; col < tam ;col++)
		{
			if(mat[lin][col]!=0)
				cont++;
		}
		int resp = tam*(tam-1) /2;

		if(cont!=resp)
			completo=1;
		


			
		if(grafo)
			printf("\nEsta matriz e um digrafo!\n");
		else
			printf("\nEsta matriz e um grafo!\n");
			
		if(simples)
			printf("Esta matriz nao e simples!\n");
		else
			printf("Esta matriz e simples!\n");
		if(regular)
			printf("Esse grafo nao e regular\n");
		else
			printf("Esse grafo e regular\n");
		if(completo)
			printf("Esse grafo nao e completo\n");
		else
			printf("Esse grafo e completo\n");	

	}
	else {
		if(strcmp(linha,"MI") == 0){// MI
			/*
			MI
			A B C D
			A,B B,D C,A D,C
			-15 0 15 0
			15 -15 0 0
			0 0 -15 15
			0 0 -15 15
			0 15 0 -15
			

			A,B B,D C,A D,C


			*/
			char aux[3];
			char linha[100];
			fgets(linha,100,ptr);
			int i=0,j=0;
			while(linha[i]!='\0')
			{
				while(linha!='\0' && linha[i]!=' ') // A,B B,D C,A D,C

				{
					aux[j]=linha[i];
					j++;
					i++;
				}
				if(aux[0] == aux[2])
					laco = 1;

			}


			//grafo ou digrafo
			int achei=0; //achei 1, nao achei 0
			for(int lin=0;lin<tam && !achei;lin++)
			{
				for(int col=0;col<tam && !achei;col++)
				{
					if(mat[lin][col] < 0)
						achei = 1;
				}
			}



			// int simples=0;
			// for(int lin=0; lin<tamV && !simples; lin++){
			// 	int cont=0;
			// 	for(int col=0; col<tamA && !simples, col++){
			// 		if(abs(mat[col][lin]) > 1)
			// 			simples = 1;
			// 	}
			// }

			
			// int regular = 0;
			// for(int lin=0; lin<tam && !regular; lin++){
			// 	int atual = 0;
			// 	for(int col=0; col<tam; col++){
			// 		atual += abs(mat[lin][col]);
			// 	}
			// 	if
			// }
			

			if(achei)
				printf("\nEsta matriz e um digrafo!\n");
			else
				printf("\nEsta matriz e um grafo!\n");
			if(laco)
				printf("\nEsta matriz nao e um simples!\n");
			else
				printf("\nEsta matriz e um grafo!\n");
			
		}
		else
		{
			if(strcmp(linha),"LA" == 0){
				char linha[100];
				int valor;
				ListaADJ* L=NULL;
				while(!feof(ptr)){
					fscanf(ptr,"%[^,],%[^\n]\n",&linha,&valor);
					char origem[2],destino[2];
					origem[0]=linha[0];
					origem[1]='\0';

					destino[0]=linha[2];
					destino[1]='\0';
					
					inserirFinalLista(L,origem,destino,valor);

					
				}
				
			}
			else{
				printf("\nErro ao ler arquivo, nome de matriz ou lista, invalido!\n");
			}
		}
	}
	
	fclose(ptr);
}
