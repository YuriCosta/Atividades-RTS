#include <stdio.h>
#include <process.h>
#include<conio.h>
#include<string.h>

////
////Aluno: Yuri de Castro Costa
////

char *palavra, letra, *indice_temp;
int flagA = 1, flagB = 1, flagC = 1, flagD = 1;

//void start_thread( char a );

//Threads
void thread_A( void *threadno)
{
    palavra = (char*) malloc(44);
    for(;;)
    {
        while(flagA == 1) {}

        printf("\nDigite uma palavra:\n");

        fgets(palavra, 11, stdin); //aceita no máximo 10 letras
        fflush(stdin);

        flagA = 1;
        flagB = 0;
    }
}

void thread_B( void *threadno)
{
    for(;;)
    {
        while(flagB == 1) {}
        printf("\nDigite uma letra:\n");

        letra = getche();

        flagB = 1;
        flagC = 0;
    }
}

void thread_C( void *threadno)
{
    for(;;)
    {
        while( flagC == 1 ) {}
        indice_temp = (char*) strchr( palavra, letra);

        if( indice_temp == NULL )
        {
            printf("\nO caracter não está contido na palavra");
            flagC = 1;
            flagA = 0;
        }
        else
        {
            printf("\nO caracter esta contido na palavra");
            flagC = 1;
            flagD = 0;
        }
    }
}

void thread_D( void *threadno)
{
    for(;;)
    {
        while( flagD == 1 ) {}
        printf("\nIndice do caracter encontrado:\n");
        printf( "%ld\n", &indice_temp[0]-&palavra[0]);
        flagD = 1;
        flagA = 0;
    }
}

//
//START THREADS
//
void start_thread()
{
    long int threadid;

    ////Criação das threads
#if defined(_WIN32_)

    if((threadid = _beginthread(thread_A, 4096, NULL)) == (unsigned long) -1 )

#else

    if((threadid = _beginthread(thread_A, 4096, NULL)) == -1)

#endif
    {
        printf("Não deu pra criar a thread A");
        return;
    }

#if defined(_WIN32_)

    if((threadid = _beginthread(thread_B, 4096, NULL)) == (unsigned long) -1 )

#else

    if((threadid = _beginthread(thread_B, 4096, NULL)) == -1)

#endif
    {
        printf("\nNão deu pra criar a thread B");
        return;
    }

#if defined(_WIN32_)

    if((threadid = _beginthread(thread_C, 4096, NULL)) == (unsigned long) -1 )

#else

    if((threadid = _beginthread(thread_C, 4096, NULL)) == -1)

#endif
    {
        printf("\nNão deu pra criar a thread C\n");
        return;
    }

#if defined(_WIN32_)

    if((threadid = _beginthread(thread_D, 4096, NULL)) == (unsigned long) -1 )

#else

    if((threadid = _beginthread(thread_D, 4096, NULL)) == -1)

#endif
    {
        printf("\nNão deu pra criar a thread D\n");
        return;
    }


    flagA = 0;

}

int main(int argc, char *argv[])
{
    start_thread();
    for(;;);
}
