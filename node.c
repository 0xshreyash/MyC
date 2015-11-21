#include<stdio.h>
void printnum( int begin )
{
    printf( "%d", begin );
    if ( begin < 9 )         /* The base case is when begin is no longer */
    {                           /* less than 9 */
        printnum ( begin + 1 ); 
    }
    /* display begin again after we've already printed everything from 1 to 9
     and from 9 to begin + 1 */
    printf( "%d", ++begin );
}
int main()
{
	printnum(1);
}
