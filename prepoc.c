#include <stdio.h>

#define DEBUG

#define MUDDLE(x,y)  (((x)<<(y))|((y)&((y)-1)))

#ifdef DEBUG
#define DEBUG_INT(x) printf("line %3d: %s=%d\n", \
		__LINE__, #x, x)
#else
#define DEBUG_INT(x)
#endif

int
main(int argc, char *argv[]) {
	int i=2, j=3;
	i = MUDDLE(i,j);
	DEBUG_INT(i);
	j = MUDDLE(j,i);
	DEBUG_INT(j);
	return 0;
}