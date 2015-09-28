#include<stdio.h>
#include<stdio.h>
void
palindrome(char c[]);
int 
main(int argc, char *argv[])
{
	char c[1000];
	gets(c);
	palindrome(c);
	return 0;
}
void
palindrome(char c[])
{
	int flag=1;
	int i,j;
	for(i=0;c[i]!='\0';i++);
	for(j=0;c[j]!='\0';j++)
	{i=i-1;
		if(!(c[i]>=65&&c[i]<=90)&&(c[i]>=97&&c[i]<=122))
		{
			i--;
			
		}
		if(i<0)
			{
				break;
			}
		if(!(c[j]>=65&&c[j]<=90)&&(c[j]>=97&&c[j]<=122))
		{
			j++;
			
		}
		if(c[j]=='\0')
			{
				break;
			}
		if(c[i]!=c[j])
		{
			flag=0;
		}
		i--;
		j++;
	}
	if(flag)
	{
		printf("The given sequence is palindrome\n");
	}
	return;
}