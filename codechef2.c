#include<math.h>
#include<string.h>
#include<stdio.h>
void main()
{
	char a[300];char b[300],c[300];int flag=0;
	printf("Enter a String");
	scanf("%s",a);
	printf("Enter word to replace the string");
	scanf("%s",b);
	printf("Enter word to be replaced");
	scanf("%s",c);
	for(int i=0;i<strlen(a);i++)
	{
		if(a[i]==c[i])
		{
			for(int j=0;j<strlen(b);j++)
			{
				if(b[j]!=a[i+j])
				{
					flag=1;
				}
			}
			if(flag==0 && a[i+strlen(b)]==" ")
			{	int m=i;
				for(int j=m;j<strlen(a);j++)
				{
					if(j<=m+strlen(b))
					{
						a[j]=a[j+strlen(b)];
					}
					else
					{
						a[j]="";
					}
				}
			}
		}
}
				printf("%s",a);

	
}
				
					
																	
	


