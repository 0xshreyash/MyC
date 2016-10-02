#include <stdio.h>
#include <stdlib.h>


char *p = "#include <stdio.h>%c#include <stdlib.h>%c%cchar *p = %c%s%c;%cint main(int argc, char *argv)%c{%cprintf(\"Thank You, Allistair\");%cprintf(p,10,10,10,34,p,34,10,10,10,10,10,10,10,10,10);%creturn 0;%c}%c";

int main(int argc, char *argv[])
{
	printf("Thank you, Allistair\n");
	printf(p,10,10,10,34,p,34,10,10,10,10,10,10,10,10);
	return 0;	
}
