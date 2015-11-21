#include<stdio.h>
int main()
{int n,temp2=0,temp=0;
int arr[]={1,2,45,98,1008};
printf("Enter element");
scanf("%d",&n);
for(int i=0;i<(sizeof(arr)/sizeof(int)+1);i++)
{
	if(arr[i]>n)
	{	temp=arr[i];
		arr[i]=n;
		for(int j=i+1;j<=(sizeof(arr)/sizeof(int)+1);j++)
		{
			temp2=arr[j];
			arr[j]=temp;
			temp=temp2;
		}
	}
}

for(int i=0;i<(sizeof(arr)/sizeof(int)+1);i++)
{
	printf("%d",arr[i]);
}
return 0;
}
			
