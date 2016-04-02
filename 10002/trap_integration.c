#include <stdio.h>
#include <stdlib.h>
#include <math.h>



void calcarea(double start, double stop, int steps);
double trapezoid(double dx, double sum_y);
double f(double x);


int main()
{
	double start, stop;
	int steps;
	printf("Enter the x-coordinate to start at:\n");
	scanf("%lf", &start );

	printf("Enter the x-coordinate to stop at:\n");
	scanf("%lf", &stop );
	printf("Enter number of steps \n");
	scanf("%d", &steps );

	calcarea(start, stop, steps);

	return 0;


}
double trapezoid(double dx, double sum_y)
{
	return (dx)*(sum_y)/2;
}

double f(double x)
{
	return (sin(5*x) + cos(10*x) + x*x/10);
}

void calcarea(double start, double stop, int steps)
{
	double totarea = 0.0, x1, x2, fx1, fx2, dx, sum_y;

	x1 =  start;
	fx1 = f(x1);

	for(int i =1; i<= steps; i++)
	{
		x2 = x1 + (double)i*(stop-start)/steps;
		fx2 = f(x2);
		dx = x2 - x1;
		sum_y = fx1 + fx2;
		totarea = totarea + trapezoid(dx, sum_y);
	}
	printf("\nThE total area is: %f\n", totarea );
}