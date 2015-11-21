#include <iostream>
using namespace std;

int factorial(int n) {
    if (n <= 1) return 1;
    else return n*factorial(n-1);
}

int nCr(int n, int r) {
    return factorial(n)/(factorial(r) * factorial(n-r));
}

int N(int x, int y) {
    return ((x+y)%2==0?x:y) + (x+y)*(x+y+1)/2;
}

int N(int x, int y, int z) {
    if(x+y+z==0) {
        return 0;
    }
    int sum = 0; //number of terms such that the sum of their coordinates < x + y + z
    for(int i = 3; i <= x+y+z+1; i++) {
        sum += nCr(i, 2);
    }
    if((x+y+z)%2==0) {
        return sum + N(y,x) + 1;
    }
    else {
        return sum + nCr(x+y+z+2, 2) - N(y,x);
    }
}

int main() 
{
    //Enter values here
    std::cout << N(0, 0, 0) << std::endl;
    std::cout << N(-21, 0, 0) << std::endl;
    std::cout << N(0, 1, 0) << std::endl;
    std::cout << N(0, 0, 1) << std::endl;
    std::cout << N(0, 0, 2) << std::endl;
    std::cout << N(0, 1, 1) << std::endl;
    std::cout << N(1, 0, 1) << std::endl;
    std::cout << N(2, 0, 0) << std::endl;
    std::cout << N(1, 1, 0) << std::endl;
    std::cout << N(0, 2, 0) << std::endl;
    std::cout << N(3, 0, 0) << std::endl;
    std::cout << N(2, 1, 0) << std::endl;

    std::cout << N(1, 2, 3) << std::endl;
    return 0;
}
