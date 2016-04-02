#include<stdio.h>
#include<math.h>
void main()
{	int n,arr[1000],i,j,sum=0;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	for(i=0;i<n;i++)
	{
		sum=arr[i];
		for(j=1;j<=((arr[i])/2);j++)
                {
                       if(arr[i]%j==0)
                        {
                                sum=sum+j;
                        }
          
		}
		printf("%d\n",sum);
		
	}
}	
