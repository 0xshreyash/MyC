#include<stdio.h>
#include<stdlib.h>
int anagram(char c[],char a[]);
void prnarr(int a[]);
int
main(int argc,char *argv[])
{
	int flag=0;
	char c[1000],a[1000];
	gets(c);
	printf("\n");
	gets(a);
	flag=anagram(a,c);
	if(flag)
	{
		printf("The two strings are anagrams\n");
	}
	else
	{
		printf("The two strings are not anagrams\n");
	}
	
	return 0;
}
int anagram(char a[],char b[])
{
	int flag=1;
	int c[26],d[26],k;
	for(k=0;k<26;k++)
	{
		c[k]=0;
		d[k]=0;
	}

	
	for(k=0;a[k]!='\0';k++)
	{
		if(a[k]>='A'&&a[k]<='Z')
		{
			int m= ((int)a[k])-65;
			c[m]++;
		}
		if(a[k]>='a'&&a[k]<='z')
		{
			int m= ((int)a[k])-97;
			c[m]++;
	}
	}

	
	
	
	for(k=0;b[k]!='\0';k++)
	{
		if(b[k]>='A'&&b[k]<='Z')
		{
			int m= ((int)b[k])-65;
			d[m]++;
			
		}
		if(b[k]>='a'&&b[k]<='z')
		{
			int m= ((int)b[k])-97;
			d[m]++;
		}
		
		
	}
	
	for(k=0;k<26;k++)
	{
		if(c[k] != d[k])
		{
			flag=0;
			break;
		}
	}
	
		return flag;
}
void prnarr(int a[])
{
	int i;
	for(i=0;i<26;i++)
	{
		printf("a[%d]=%d ",i,a[i]);
	}
	printf("\n");
}
	