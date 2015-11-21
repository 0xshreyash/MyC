double bisection(double x1, double x2, double eps, int limit) 
{
	double fx1, fx2, mid, fmid; 

	int iterations=0; 
	fx1 = f(x1); 
	fx2 = f(x2);
	while (x2-x1 > eps) 
	{ 
		iterations = iterations+1; if (iterations==limit) 
		{
			exit(NOT_CONVERGING);
		} 
		mid = (x1+x2)/2; fmid = f(mid); 
		if (fx1*fmid < 0) 
		{
			 x2 = mid; fx2 = fmid; /* root is to left of middle */
		}
	 	else 
	    {  
	   		x1 = mid; fx1 = fmid;	
	    }
	} 
	printf("(bisection) eps=%.1e, iterations=%d\n",eps, iterations); 
	return (x1+x2)/2;
}
 
