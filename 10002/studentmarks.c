#include<stdio.h>
#include<stdlib.h>
#define n 1000
int
main(int charc, char * charv[])
{
	int arrn[n],arrm[n],stdnum=0,stdm=0,size=0,i,j;
	printf("Enter the student number followed by the marks obtained by the student\n");
	while(scanf("%d  %d",&stdnum,&stdm)==2)
	{
		if(size<n)
		{
			arrn[size]=stdnum;
			arrm[size]=stdm;
			size++;

		}
		else
		{
			printf("Too many entries given program needs to abort");
			exit(EXIT_FAILURE);
		}
	}
	printf("Student Number    Marks\n");
				for(i=0;i<size-1;i++)
				{
					for(j=i+1;j<size;j++)
					{
						if(arrn[i]>arrn[j])
						{int temp;
							temp=arrn[i];
							arrn[i]=arrn[j];
							arrn[j]=temp;
							temp=arrm[i];
							arrm[i]=arrm[j];
							arrm[j]=temp;
						}
					}
				}
				for(i=0;i<size;i++)
				{
					printf("     %d         %d     \n",arrn[i],arrm[i]);
				}
}
