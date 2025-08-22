// Maria Eduarda Ribeiro Nunes RA:102317429
// Gabriel Baldassarini Savoldi RA:102316449

#include <stdio.h>
#include <string.h>
#include <math.h>
#include<conio2.h>
#define MAX 10

struct ListaADJ
{
    char origem[2], destino[2];
    int valor;
    ListaADJ *prox;
};

ListaADJ *novaLista(char origem[2], char destino[2], int valor)
{
    ListaADJ *nova = new (ListaADJ);
    strcpy(nova->origem, origem);
    strcpy(nova->destino, destino);
    nova->valor = valor;
    nova->prox = NULL;
    return nova;
}

void inserirFinalLista(ListaADJ **L, char origem[2], char destino[2], int valor)
{
    ListaADJ *aux, *nova = novaLista(origem, destino, valor);
    aux = *L;
    if (*L == NULL)
    {
        *L = nova;
    }
    else
    {
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = nova;
    }
}

int main()
{
    int mat[MAX][MAX], tam = 0;
    char linha[20];
    FILE *ptr = fopen("Entrada.txt", "r");
 	fscanf(ptr,"%[^\n]\n",&linha);
    if (strcmp(linha, "MA") == 0) // MATRIZ DE ADJACENCIA
    {
    	
        fscanf(ptr,"%[^\n]\n",&linha);
        int tam = 0, i = 0;
        while (linha[i] != '\0')
        { // A B C D
            if (linha[i] != '\0' && linha[i] != ' ')
                tam++;
            i++;
        }
        
        int jogo=0;
        for(int lin=0;lin<tam;lin++)
        {
    		for(int col=0;col<tam;col++)
    		{
    			fscanf(ptr,"%d",&jogo);
    			mat[lin][col]=jogo;
    		}
        }
        
/*
        for (int i = 0; i < tam; i++)
        {
            for (int j = 0; j < tam; j++)
            {
                fscanf(ptr,"%[^\n]\n",&linha);
                int aux = 0;
                while (linha[aux] != '\0')
                {
                	if(linha[aux] != ' ')
                    	mat[i][j] = linha[aux] - 48;
                    aux++;
                }
            }
        }
*/
		for(int lin=0;lin<tam;lin++){
			for(int col=0;col<tam;col++)
			{
				printf("%d ",mat[lin][col]);
			}
			printf("\n");
		}
	

        // grafo ou diagrafo
        int grafo = 0; // achei 1, nao achei 0
        for (int lin = 0, col = 0; lin < tam && !grafo; lin++)
        {
            if (mat[lin][col] != mat[col][lin]) // digrafo
                grafo = 1;
        }
        for (int lin = tam - 1, col = 0; col < tam && !grafo; col++)
        {
            if (mat[lin][col] != mat[col][lin]) // digrafo
                grafo = 1;
        }
        
        

        // simples (sem laco)
        int simples = 0;
        for (int lin = 0; lin < tam && !simples; lin++)
        {
            if (mat[lin][lin] != 0)
                simples = 1; // tem laco
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

        // Regular origem
        int ori=0,des=0,antOri=0,antDes=0,regOri=0;
		for(int lin=0;lin<tam && !regOri;lin++)//dando la ele
		{
			ori=0;
			for(int col=0;col<tam && !regOri;col++)
			{
				if(mat[lin][col]>0)
					ori++;
			}
			if(antOri==0)
				antOri=ori;
			else
				if(antOri!=ori)
					regOri=1;	
		}
		
		//regular Destino
		int regDes=0;
		for(int col=0;col<tam && !regDes;col++)//dando la ele
		{
			des=0;
			for(int lin=0;lin<tam && !regDes;lin++)
			{
				if(mat[lin][col]>0)
					des++;
			}
			if(antDes==0)
				antDes=des;
			else
				if(antDes!=des)
					regDes=1;	
		}

		
			
		
        // completo
        int completo=0;
        if(!simples)
        {
        	int cont = 0;
	        for (int lin = 0; lin < tam; lin++)
	        {
	        	for(int col=0;col<tam;col++){
	        		if (mat[lin][col] != 0)
	                	cont++;
	        	}
	        }
	        int resp;
	        if(!grafo)
	        	resp = tam * (tam - 1);
	        else
	        	resp = tam * (tam - 1)/2;
			printf("cont %d\nresp: %d\n",cont,resp);
	        if (cont >= resp)
	            completo = 1;	
        }
    	else
    	{
    		completo=1;
    	}
        
        if (grafo)
            printf("\nEsta Matriz de Adjacencia e um Digrafo!\n");
        else
            printf("\nEsta Matriz de Adjacencia e um Grafo!\n");

        if (simples)
            printf("Esta Matriz de Adjacencia nao e Simples!\n");
        else
            printf("Esta Matriz de Adjacencia e Simples!\n");
            
        if (regOri)
            printf("Essa Matriz de Adjacencia nao e Regular de Emissao!\n");
        else
            printf("Essa Matriz de Adjacencia e Regular de Emissao!\n");
            
        if (regDes)
            printf("Essa Matriz de Adjacencia nao e Regular de Recepcao!\n");
        else
            printf("Essa Matriz de Adjacencia e Regular de Recepcao!\n");
        
        if (!completo)
            printf("Essa Matriz de Adjacencia nao e Completo!\n");
        else
            printf("Essa Matriz de Adjacencia e Completo!\n");
    
    }
    else
    {
        if (strcmp(linha, "MI") == 0)
        { // MI
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
            int i = 0, j = 0;
            fscanf(ptr,"%[^\n]\n",&linha);
            int tamV = 0, tamA = 0;
            while (linha[i] != '\0')
            { // A B C D
                if (linha[i] != '\0' && linha[i] != ' ')
                    tamV++;
                i++;
            }
            
            
            
            fscanf(ptr,"%[^\n]\n",&linha);
            printf("linha : %s\n",linha);
            char laco=0;
            while (linha[i] != '\0')
            {
            	printf("b\n");
                while (linha[i] != '\0' && linha[i] != ' ')
                { // A,B B,D C,A D,C
                    aux[j] = linha[i];
                    j++;
                    i++;
                }
                if (j > 0)
                {
                	printf("a\n");
                    tamA++; // conta aresta
                    if (aux[0] == aux[2])
                    {
                        laco = 1;
                    }
                    j = 0;
                }
                i++;
            }
            
			int jogo=0;
            for (int i = 0; i < tamV; i++)
            {
                for (int j = 0; j < tamA; j++)
                {
                    fscanf(ptr,"%d",&jogo);
                	mat[i][j] = jogo;
                }
            }


			
            for (int lin = 0; lin < tamV; lin++)
            {
                for (int col = 0; col < tamA ; col++)
                {
                    printf("%d",mat[lin][col]);
                }
                printf("\n");
            }



            // grafo ou digrafo
            int achei = 0; // achei 1, nao achei 0
            for (int lin = 0; lin < tamV && !achei; lin++)
            {
                for (int col = 0; col < tamA && !achei; col++)
                {
                    if (mat[lin][col] < 0)
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

            // regular
            //  int regular = 0;
            //  for(int lin=0; lin<tamV; lin++){
            //  	for(int col=0; col<tamA; col++){
            //  		atual += abs(mat[lin][col]);
            //  	}
            //  	if
            //  }

            // regular
            char regEmi=0,regRec=0;
            int neg = 0, pos = 0, atualN = 0, atualP = 0;
            for (int lin = 0; lin < tamV; lin++)
            {
                for (int col = 0; col < tamA; col++)
                {
                    if (mat[lin][col] > 0)
                        pos++;
                    else if (mat[lin][col] < 0)
                        neg++;
                    if (atualN != 0 || atualP != 0)
                    {
                    	if (atualN != neg)
                    		regEmi=1;
                    	if(atualP != pos)
                    		regRec=1;
                    }
                    atualN = neg;
                    atualP = pos;
                    pos = 0;
                    neg = 0;
                }
            }
            
            
            

            // completo
            int cont = 0, completo = 0;
            for (int lin = 0, col = 0; col < tamA; col++)
            {
                if (mat[lin][col] > 0)
                    cont++;
            }
            int resp = tamA * (tamA - 1) / 2;

            if (cont != resp)
                completo = 1;

            if (achei)
                printf("\nEsta Matriz de Incidencia e um Digrafo!\n");
            else
                printf("\nEsta Matriz de Incidencia e um Grafo!\n");
                
            if (laco)
                printf("\nEsta Matriz de Incidencia nao e Simples!\n");
            else
                printf("\nEsta Matriz de Incidencia e Simples!\n");
                
            if (completo)
                printf("\nEsta Matriz de Incidencia nao e Completa!\n");
            else
                printf("\nEsta Matriz de Incidencia e Completa!\n");
                
            if (regEmi)
                printf("\nEsta Matriz de Incidencia nao e Regular de Emissao!\n");
            else
                printf("\nEsta Matriz de Incidencia e Regular de Emissao!\n");
                
            if (regRec)
                printf("\nEsta Matriz de Incidencia nao e Regular de Recepcao!\n");
            else
                printf("\nEsta Matriz de Incidencia e Regular de Recepcao!\n");
        }
        else
        {
            if (strcmp(linha, "LA") == 0){
            
                int tam = 0;
                char linha[100];
                int valor;
                char origem[2], destino[2];
                ListaADJ *L = NULL;
                 //0
                //fscanf(ptr, "%[^,],%[^\n]\n", &linha, &valor);
                while (fscanf(ptr, "%[^,],%[^\n]\n", &linha, &valor) == 2) // poderia ser != EOF ou != 0
                {
                    tam++;
                    origem[0] = linha[0];
                    origem[1] = '\0';
                    destino[0] = linha[2];
                    destino[1] = '\0';
                    inserirFinalLista(&L, origem, destino, valor);
                }
                
                ListaADJ *aux, *atual;
                atual = L;
                char digrafo = 0;
                while (atual != NULL && !digrafo) // digrafo
                {
                    digrafo = 1;
                    aux = atual->prox;
                    while (aux != NULL && digrafo)
                    {
                        if (strcmp(atual->origem, aux->destino) == 0 && strcmp(atual->destino, aux->origem) == 0)
                            digrafo = 0;
                        aux=aux->prox;
                    }
                    atual = atual->prox;
                }
                atual = L;
                char simples = 0;
                while (atual != NULL && !simples) // verifica se tem laco O(n)
                {
                    if (strcmp(atual->origem, atual->destino) == 0)
                        simples = 1;
                    atual = atual->prox;
                }
                atual = L;
                
                
                
                while (atual != NULL && !simples) // verifica multi aresta O(n^2)
                {
                    aux = atual->prox;
                    while (aux != NULL && !simples)
                    {
                        if (strcmp(atual->origem, aux->origem) == 0 && strcmp(atual->destino, aux->destino) == 0)
                            simples = 1;
                        aux=aux->prox;
                    }
                    atual = atual->prox;
                }
                atual = L;
                char in = 1, out = 1;
                int pos = 0, antP = 0, neg = 0, antN = 0;
                while (atual != NULL && (in || out)) // verifica regular O(n^2)
                {
                    aux = L;
                    while (aux != NULL && (in || out))
                    {
                        if (in)
                            if (strcmp(atual->origem, aux->origem) == 0)
                            {
                                pos++;
                            }
                            else if (out)
                                if (strcmp(atual->origem, aux->destino) == 0)
                                {
                                    neg++;
                                }
                        aux=aux->prox;
                    }
                    if (antP == 0 && antN == 0)
                    {
                        antP = pos;
                        antN = neg;
                    }
                    else
                    {
                        if (antN != neg)
                            out = 0;
                        if (antP != pos)
                            in = 0;
                    }
                    pos = 0;
                    neg = 0;
                    atual = atual->prox;
                }
				
                // completo

                char completo;
                int cont = 0;

               
                int v[123];
                for (int i = 0; i < 123; i++)
                    v[i] = 0;
                atual = L;
                while (atual != NULL)
                {
                    if (v[atual->origem[0]] == 1)
                        cont++;
                    if (v[atual->destino[0]] == 1)
                        cont++;
					v[atual->origem[0]] = 1;
                    v[atual->destino[0]] = 1;
                    atual = atual->prox;
                }
                int resp = tam * (tam - 1); // acho q se dividir por 2 vira completo de digrafo ou sla.
                int respAtual= cont * (cont-1);
                if (resp < cont)
                    completo = 0;
                else
                    completo = 1;
               
				
                if (digrafo)
                    printf("\nEssa Lista Adjacencia e um Digrafo!\n");
                else
                    printf("\nEssa Lista Adjacencia e um Grafo!\n");
                if (!simples)
                    printf("\nEssa Lista Adjacencia e Simples!\n");
                else
                    printf("\nEssa Lista Adjacencia nao e simples!\n");

                if (in)
                    printf("\nEssa Lista Adjacencia e Regular de Recepcao!\n");
                if (out)
                    printf("\nEssa Lista Adjacencia e Regular de Emissao!\n");
                if (!in && !out)
                    printf("\nEssa Lista Adjacencia nao e Regular!\n");
                if (completo)
                    printf("\nEssa Lista Adjacencia e Completa!\n");
                else
                    printf("\nEssa Lista Adjacencia nao e Completa!\n");
            }
            else
            {
                printf("\nErro ao ler arquivo, nome de matriz ou lista, invalido!\n");
            }
        }
    }
    fclose(ptr);
}