#include<pthread.h>

int arr[1000];
int sum = 0;


void init(int *arr,int SIZE)
{
	for(int i=0;i<SIZE;i++)
	{
		arr[i] = i;
	}
}

void * sumArray(void *arg)
{
	int start = (int *)arg;
	int tempSum = 0;
	for(int i = start;i<start+100;i++)
	{
		tempSum+= arr[i];
	}
	
	sum = sum+tempSum;
}

int main()
{
	pthread_t threads[10];
	init(arr,1000);
	for(int i=0;i<10;i++)
	{
		pthread_create(&threads[i],NULL,sumArray,(void*)(i*100));
	}

	for(int i=0;i<10;i++)
	{
		pthread_join(threads[i],NULL);
	}
	
	printf("Total Sum : %d\n",sum);

return 0;
}
