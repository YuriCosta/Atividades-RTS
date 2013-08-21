#include <stdio.h>
#include <stdlib.h>
#include <process.h>
////
////Aluno: Yuri de Castro Costa
////
long int listaid[6];
int flag = 1, sao_diferentes_flag = 1;

////Fun��es de uso geral
//retorna 1 se todos os itens do array s�o diferentes, 0 sen�o
int sao_diferentes( long int *array, int lenght)
{
    int i, j;
    for(i = 0; i < lenght; i++)
    {
        for(j = i+1; j < lenght; j++)
        {
            if( array[i] == array[j] )
            {
                return(0);
            }
        }
    }

    return (1);
}

////Merge Short: N�o foi criado por mim,
////apenas editei para trabalhar com long int
void merge(long int vec[], int vecSize)
{
    long int mid;
    long int i, j, k;
    long int* tmp;

    tmp = (long int*) malloc(vecSize * sizeof(long int));
    if (tmp == NULL)
    {
        exit(1);
    }

    mid = vecSize / 2;

    i = 0;
    j = mid;
    k = 0;
    while (i < mid && j < vecSize)
    {
        if (vec[i] < vec[j])
        {
            tmp[k] = vec[i++];
        }
        else
        {
            tmp[k] = vec[j++];
        }
        ++k;
    }

    if (i == mid)
    {
        while (j < vecSize)
        {
            tmp[k++] = vec[j++];
        }
    }
    else
    {
        while (i < mid)
        {
            tmp[k++] = vec[i++];
        }
    }

    for (i = 0; i < vecSize; ++i)
    {
        vec[i] = tmp[i];
    }

    free(tmp);
}

void mergeSort(long int vec[], int vecSize)
{
    long int mid;

    if (vecSize > 1)
    {
        mid = vecSize / 2;
        mergeSort(vec, mid);
        mergeSort(vec + mid, vecSize - mid);
        merge(vec, vecSize);
    }
}

//Threads
void thread_1( void *threadno)
{
    printf("\nProcesso 1 Criado!\n");
    while( flag )
    {}
}

void thread_2( void *threadno)
{
    printf("\nProcesso 2 Criado!\n");
    while( flag )
    {}
}

void thread_3( void *threadno)
{
    printf("\nProcesso 3 Criado!\n");
    while( flag )
    {}
}

void thread_4( void *threadno)
{
    printf("\nProcesso 4 Criado!\n");
    while( flag )
    {}
}

void thread_5( void *threadno)
{
    printf("\nProcesso 5 Criado!\n");
    while( flag )
    {}
}

void thread_6( void *threadno)
{
    printf("\nProcesso 6 Criado!\n");

    while( flag )
    {
        ////Espera a fun��o start_thread informar que os ids s�o distintos
        if( sao_diferentes_flag == 0 ) 
        {
            mergeSort( listaid, 6); //...ordena a lista
            
            int i;
            for( i = 0; i < 6; i++)
            {
                printf( "\n%ld", listaid[i]); ////Mostra o vetor ordenado
            }
            printf("\n");

            sao_diferentes_flag = 0;
            flag = 0; ////Mata todas as threads
        }
    }
}



//
//START THREADS
//
void start_thread()
{
    flag = 1; //Mant�m as threads vivas

    ////Cria��o das threads
#if defined(_WIN32_)

    if((listaid[0] = _beginthread(thread_1, 4096, NULL)) == (unsigned long) -1 )

#else

    if((listaid[0] = _beginthread(thread_1, 4096, NULL)) == -1)

#endif
    {
        printf("N�o deu pra criar a thread 1");
        return;
    }

#if defined(_WIN32_)

    if((listaid[1] = _beginthread(thread_2, 4096, NULL)) == (unsigned long) -1 )

#else

    if((listaid[1] = _beginthread(thread_2, 4096, NULL)) == -1)

#endif
    {
        printf("\nN�o deu pra criar a thread 2");
        return;
    }

#if defined(_WIN32_)

    if((listaid[2] = _beginthread(thread_3, 4096, NULL)) == (unsigned long) -1 )

#else

    if((listaid[2] = _beginthread(thread_3, 4096, NULL)) == -1)

#endif
    {
        printf("\nN�o deu pra criar a thread 3\n");
        return;
    }

#if defined(_WIN32_)

    if((listaid[3] = _beginthread(thread_4, 4096, NULL)) == (unsigned long) -1 )

#else

    if((listaid[3] = _beginthread(thread_4, 4096, NULL)) == -1)

#endif
    {
        printf("\nN�o deu pra criar a thread 4\n");
        return;
    }

#if defined(_WIN32_)

    if((listaid[4] = _beginthread(thread_5, 4096, NULL)) == (unsigned long) -1 )

#else

    if((listaid[4] = _beginthread(thread_5, 4096, NULL)) == -1)

#endif
    {
        printf("\nN�o deu pra criar a thread 5\n");
        return;
    }

#if defined(_WIN32_)

    if((listaid[5] = _beginthread(thread_6, 4096, NULL)) == (unsigned long) -1 )

#else

    if((listaid[5] = _beginthread(thread_6, 4096, NULL)) == -1)

#endif
    {
        printf("\nN�o deu pra criar a thread 6\n");
        return;
    }

    if(sao_diferentes( listaid, 6) == 1 )//Se todos os ids forem diferentes...
    {
        
        //...seta a flag, assim a thread 6 ordenar� a lista e a mostra.
        sao_diferentes_flag = 0;
    }
    else   //Sen�o mata todas as threads e reinicia o m�todo
    {
        flag = 0;
        start_thread();
    }
}

int main(int argc, char *argv[])
{
    start_thread();
    system("pause");
    return 0;
}
