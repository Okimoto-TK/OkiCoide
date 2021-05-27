#include <iostream>
#include <math.h>
#include <stdio.h>
using namespace std;
int main(int argc, char const *argv[])
{
	double a, b, c, d;
	cin >> a >> b >> c >> d;
	for(double i = -100.00000; i <= 100.00000; i += 0.00001){
		double sum = a * i * i * i;
		sum += b * i * i;
		sum += c * i;
		sum += d;
		if(abs(sum) < 0.0000001)
			printf("%.2f ", i);
	}
	return 0;
}