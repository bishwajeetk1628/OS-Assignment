#include <stdlib.h>
#include<stdio.h>
#include <pthread.h>
#include<unistd.h>
#include<sys/types.h>

int no_of_thread,k=0;
void *pi_func(void *p);
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
double q=0,p16=1,pi_value=0,sum=0;

void *pi_func(void * p)
{
    int RaceCond;
    int k=(int)p;
    pi_value+= 1.0/p16 * (4.0/(8* k + 1) - 2.0/(8*k + 4)- 1.0/(8*k + 5) - 1.0/(8*k+6));
    pthread_mutex_lock(&lock);
    p16 *=16;
    RaceCond=pthread_mutex_unlock(&lock);
    if(RaceCond)								// constant complexity O(1)
	{
        printf("error is %d\n", RaceCond);
    }
    pthread_exit(&pi_value); 
}
int main()
{
	printf("\nNOTE : The value of pi for single thread is 3.14159");
	printf("\nPlease! Enter -1 to exit ");
	printf("\n\nEnter the number of threads = ");
	scanf("%d",&no_of_thread);
	do
	{
		if(no_of_thread==-1)			//  constant complexity O(1)
		{
			exit(0);
		}
		else if(no_of_thread<=0 || no_of_thread==1)			
		{
			printf("\nError : please enter number of thread more than 1 ");
		}
		else
		{
		    pthread_t threads[no_of_thread];
		    int assign; 
		    int i;
		    pthread_mutex_init(&lock,NULL);
		    for(i=0;i<no_of_thread;i++)
			{
		        assign= pthread_create(&threads[i],NULL,pi_func,(void *)i);
		        if(assign)
				{
		            printf("Error found in  pthread_create() is %d\n", assign);
		        }
		    }
		    for(i=0;i<no_of_thread;i++)			//	constant complexity O(n)
			{
		        assign=pthread_join(threads[i],NULL);
		        if(assign)
				{
		            printf("Error found in  pthread_create() is %d\n", assign);
		        }
		        q=q+pi_value; 
		    }
		    pthread_mutex_destroy(&lock);
		    printf("\nProgram sucessfully executed.\n\n");
		    printf("The value of pi is  : %f for %d threads",q,no_of_thread);
		    
	    }
	    printf("\nEnter the number of threads=");
		scanf("%d",&no_of_thread);
	}while(no_of_thread!=-1);					// constant complexity O(n)
	
}			//The overall complexity of the program is O(n^2)




