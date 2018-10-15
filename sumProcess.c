#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void initiliaze(int *arr, int SIZE)
{
	for(int i=0;i<SIZE;i++)
	{
		arr[i] = i;
	}

}

int main()
{
	int arr[1000];
	int sum[2];
	int limit[2];

	int summ = 0,limitt =0;
	int pid;

	initiliaze(arr,1000);
	if(pipe(sum) == -1)
	{
	    printf("pipe failed");
	    return 1;
	}
	if(pipe(limit) == -1)
	{
	    printf("pipe failed");
	    return 1;
	}


	write(sum[1],&summ,sizeof(int));
	write(limit[1],&limitt,sizeof(int));

	for(int i =0 ;i<10;i++)
	{

		if((pid=fork()) == 0)
		{
			int s,l;

			read(sum[0],&s,sizeof(int));
			//printf("Readed Sum %d\n",s);

			read(limit[0],&l,sizeof(int));
			//printf("Readed Limit is: %d\n",l);

			int j = l;
			for(;j<l+100;j++)
			    s = s + arr[j];
			//printf("Writing Sum %d\n",s);

			write(sum[1],&s,sizeof(int));
			exit(0);
		}
		if(pid>0)
		{
			wait(NULL);

			read(sum[0],&summ,sizeof(int));
			//printf("Sum is : %d\n",summ);

			write(sum[1],&summ,sizeof(int));
			limitt = (i+1) * 100;
			write(limit[1],&limitt,sizeof(int));
		}
	}
	printf("Sum of Array is  : %d\n",summ);
}











