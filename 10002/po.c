#include <stdio.h>
    int main()
    {
        int i = 10;
        void *p = &i;
        printf("%f\n", *(float*)p);
        return 0;
    }
