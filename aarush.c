#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define MAXTEST 100
#define MAXHOUSE 1000
int
main(int argc, char* argv[])
{
	char a[MAXHOUSE];
	char b[MAXHOUSE];
	int i=0,c=0;
	gets(a);
	
	for(i=0;a[i]!='\0';i++)
	{
		int j;
		c=0;
		
				if((a[i]=='a')||(a[i]=='e')||(a[i]=='i')||(a[i]=='o')||(a[i]=='u')||(a[i]=='A')||(a[i]=='E')||(a[i]=='I')||(a[i]=='O')||(a[i]=='U'))
				{
					for(j=i;(a[j]!=' ')&&(a[j]!='.');j++)
					{
						if(i==0)
						{
							printf("%c",toupper(a[j]));
						}
						else
						{
							
						printf("%c",a[j]);
						}
					}
					if(i==0||a[i-1]==' ')
					{
						if(a[j+1]=='.')
						printf("way.");
					else
						printf("way");
					}
					else
					{
						for(int k=0;b[k]!='\0';k++)
						{
							printf("%c",b[k]);
						}
						if(a[j+1]=='.')
						printf("ay.");
					else
						printf("ay");
					}
					i=j;
				}
				else
				{
					if(i==0)
					{
						
					b[c]=tolower(a[i]);
					}
					else
					{
						b[c]=a[i];
					}
					c++;
				}
	}

}
					
	