#include <stdio.h>

int
main(int argc, char *argv[]) {
	char *p = "Cheshire:-)";
	while (*p) {
		printf("p = %12p, string at p = %s\n", p, p);
		p = p+1;
	}
	return 0;
}