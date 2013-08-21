#include <stdio.h>
#include <stdlib.h>
#include <process.h>
////
////Aluno: Yuri de Castro Costa
////
char listachar[32];
char flags[3] = { 0, 0, 0}; //flags[0] => flag A ; flags[1] => flag B ; flags[2] => flag C
	 
int i = 0;

void thread_A( void *threadno)
{
	while( i < 28 )
	{
		while(flags[2] == 0)
		{}
		listachar[i] = 'A';
		i++;
		flags[2] = 0;
		flags[0] = 1;
		
	}
}

void thread_B( void *threadno)
{
	while( i < 28 )
	{
		while(flags[0] == 0)
		{}
		listachar[i] = 'B';
		i++;
		flags[0] = 0;
		flags[1] = 1;
	}
}

void thread_C( void *threadno)
{
	while( i < 28 )
	{
		while(flags[1] == 0)
		{}
		listachar[i] = 'C';
		i++;
        flags[1] = 0;
		flags[2] = 1;
	}
	
	int j = 0;
	printf(listachar);
}

void start_thread()
{
	long int thread_id;
	#if defined(_WIN32_)
	
		if((thread_id = _beginthread(thread_A, 4096, NULL)) == (unsigned long) -1 )
	
	#else
	
		if((thread_id = _beginthread(thread_A, 4096, NULL)) == -1)
	
	#endif
	{
		printf("Não deu pra criar a thread A");
		return;
	}
	
	#if defined(_WIN32_)
	
		if((thread_id = _beginthread(thread_B, 4096, NULL)) == (unsigned long) -1 )
	
	#else
	
		if((thread_id = _beginthread(thread_B, 4096, NULL)) == -1)
	
	#endif
	{
		printf("\nNão deu pra criar a thread B");
		return;
	}
	
	#if defined(_WIN32_)
	
		if((thread_id = _beginthread(thread_C, 4096, NULL)) == (unsigned long) -1 )
	
	#else
	
		if((thread_id = _beginthread(thread_C, 4096, NULL)) == -1)
	
	#endif
	{
		printf("\nNão deu pra criar a thread C\n");
		return;
	}
	
	flags[2] = 1;
}

int main(int argc, char *argv[]) 
{
    listachar[30] = '\n';
	listachar[31] = '\0';
	start_thread();
	system("pause");
	return 0;
}
