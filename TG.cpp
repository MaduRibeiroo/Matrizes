// Maria Eduarda Ribeiro Nunes RA:102317429
// Gabriel Baldassarini Savoldi RA:102316449

#include <stdio.h>
#include <string.h>
#include <math.h>
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
    char linha[25];
    FILE *ptr = fopen("teste.txt", "r");

    if (strcmp(linha, "MA") == 0) // MATRIZ DE ADJACENCIA
    {
        fgets(linha, 100, ptr);
        int tam = 0, i = 0;
        while (linha[i] != '\0')
        { // A B C D
            if (linha[i] != '\0' && linha[i] != ' ')
                tam++;
            i++;
        }

        for (int i = 0; i < tam; i++)
        {
            for (int j = 0; j < tam; j++)
            {
                fgets(linha, 100, ptr);
                int aux = 0;
                while (linha != '\0' && linha[aux] != ' ')
                {
                    mat[i][j] = linha[aux] - 48;
                    aux++;
                }
            }
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

        // Regular
        int grau = 0, atual = 0, tl = 0, regular = 0;
        for (int lin = 0; lin < tam && !regular; lin++)
        {
            atual = 0;
            for (int col = 0; col < tam && !regular; col++)
            {
                if (lin == 0)
                {
                    grau += mat[lin][col];
                }
                else
                {
                    atual += mat[lin][col];
                }
            }
            if (grau != atual)
                regular = 1;
        }

        for (int col = 0; col < tam && !regular; col++)
        {

            atual = 0;
            for (int lin = 0; lin < tam && !regular; lin++)
            {
                {
                    if (lin == 0)
                    {
                        atual += mat[lin][col];
                    }
                }
                if (atual != grau)
                    regular = 1;
            }

            // completo
            int cont = 0, completo = 0;
            for (int lin = 0, col = 0; col < tam; col++)
            {
                if (mat[lin][col] != 0)
                    cont++;
            }
            int resp = tam * (tam - 1) / 2;

            if (cont != resp)
                completo = 1;

            if (grafo)
                printf("\nEsta matriz e um digrafo!\n");
            else
                printf("\nEsta matriz e um grafo!\n");

            if (simples)
                printf("Esta matriz nao e simples!\n");
            else
                printf("Esta matriz e simples!\n");
            if (regular)
                printf("Esse grafo nao e regular\n");
            else
                printf("Esse grafo e regular\n");
            if (completo)
                printf("Esse grafo nao e completo\n");
            else
                printf("Esse grafo e completo\n");
        }
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
            fgets(linha, 100, ptr);
            int tamV = 0, tamA = 0;
            while (linha[i] != '\0')
            { // A B C D
                if (linha[i] != '\0' && linha[i] != ' ')
                    tamV++;
                i++;
            }

            fgets(linha, 100, ptr);
            char laco=0;
            while (linha[i] != '\0')
            {
                while (linha[i] != '\0' && linha[i] != ' ')
                { // A,B B,D C,A D,C
                    aux[j] = linha[i];
                    j++;
                    i++;
                }
                if (j > 0)
                {
                    tamA++; // conta aresta
                    if (aux[0] == aux[2])
                    {
                        laco = 1;
                    }
                    j = 0;
                }
                i++;
            }

            for (int i = 0; i < tamV; i++)
            {
                for (int j = 0; j < tamA; j++)
                {
                    fgets(linha, 100, ptr);
                    int aux = 0;
                    while (linha != '\0' && linha[aux] != ' ')
                    {
                        mat[i][j] = linha[aux] - 48;
                        aux++;
                    }
                }
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
            char regular=0;
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
                        if (atualN != neg || atualP != pos)
                            regular = 1;
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
                printf("\nEsta matriz e um digrafo!\n");
            else
                printf("\nEsta matriz e um grafo!\n");
            if (laco)
                printf("\nEsta matriz nao e simples!\n");
            else
                printf("\nEsta matriz e simples!\n");
            if (completo)
                printf("\nEsta matriz nao e completa!\n");
            else
                printf("\nEsta matriz e completa!\n");
            if (regular)
                printf("\nEsta matriz nao e regular!\n");
            else
                printf("\nEsta matriz e regular!\n");
        }
        else
        {
            if (strcmp(linha, "LA") == 0)
            {
                int tam = 0;
                char linha[100];
                int valor;
                char origem[2], destino[2];
                ListaADJ *L = NULL;
                fscanf(ptr, "%[^,],%[^\n]\n", &linha, &valor);
                while (!feof(ptr))
                {
                    tam++;
                    origem[0] = linha[0];
                    origem[1] = '\0';
                    destino[0] = linha[2];
                    destino[1] = '\0';
                    inserirFinalLista(&L, origem, destino, valor);
                    fscanf(ptr, "%[^,],%[^\n]\n", &linha, &valor);
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
                simples = 0;
                while (atual != NULL && !simples) // verifica multi aresta O(n^2)
                {
                    simples = 1;
                    aux = atual;
                    while (aux != NULL && simples)
                    {
                        if (strcmp(atual->origem, aux->origem) == 0 && strcmp(atual->destino, aux->destino) == 0)
                            simples = 0;
                    }
                    atual = atual->prox;
                }

                atual = L;
                char in = 1, out = 1;
                int pos = 0, antP = 0, neg = 0, antN = 0;
                while (atual != NULL && (in || out)) // verifica regular O(n^2)
                {
                    aux = atual;
                    while (aux != NULL && (in || out))
                    {
                        if (out)
                            if (strcmp(atual->origem, aux->origem) == 0)
                            {
                                pos++;
                            }
                            else if (in)
                                if (strcmp(atual->destino, aux->destino) == 0)
                                {
                                    neg++;
                                }
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

                if (in || out)
                {
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
                    int resp = tam * (tam - 1) / 2;
                    if (resp != cont)
                        completo = 0;
                    else
                        completo = 1;
                }
                else
                {
                    completo = 0;
                }

                if (digrafo)
                    printf("\nEssa Lista Adj. e um Digrafo!\n");
                else
                    printf("\nEssa Lista adj. e um Grafo!\n");
                if (simples)
                    printf("\nEssa Lista Adj. e Simples!\n");
                else
                    printf("\nEssa Lista adj. nao e simples!\n");

                if (in)
                    printf("\nEssa Lista Adj. e Regular de Recepcao!\n");
                if (out)
                    printf("\nEssa Lista Adj. e Regular de Emissao!\n");
                if (!in && !out)
                    printf("\nEssa Lista Adj. nao e Regular!\n");
                if (completo)
                    printf("\nEssa Lista Adj. e Completa!\n");
                else
                    printf("\nEssa Lista adj. nao e Completa!\n");
            }
            else
            {
                printf("\nErro ao ler arquivo, nome de matriz ou lista, invalido!\n");
            }
        }
    }
    fclose(ptr);
}