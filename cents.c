#include<stdio.h>
#include<stdlib.h>
int try_one_coin(int *cents, int coin);
void print_change(int cents);
int round_to_5(int cents);
int 
main(int argc, char *argv[]){
	int cents=0,coin=50,num=0;
	printf("Enter value in cents:");
	scanf("%d",&cents);
	num=try_one_coin(&cents,coin);
	
	coin=20;
	num=try_one_coin(&cents,coin);
	
	coin=10;
	num=try_one_coin(&cents,coin);
	
	coin=5;
	num=try_one_coin(&cents,coin);
	
	coin=2;
	num=try_one_coin(&cents,coin);
	
	coin=1;
	num=try_one_coin(&cents,coin);
	printf("\n");
	
}
int try_one_coin(int *cents, int coin)
{int num=0;int static flag=0;
	if(*cents>=coin)
	{
		
		num++;
	    *cents=(*cents)-coin;
	    num=num+try_one_coin(cents,coin);
	    printf("%d ",coin);
	 l  
	    
	}
		
	return num;
}

	    
		
	