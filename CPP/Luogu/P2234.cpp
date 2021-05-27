#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
int n;
int sum;
vector <int> v;
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	v.push_back(-2147483648);
	for(int i = 0; i < n; i ++){
		int x;
		scanf("%d", &x);
		if(i == 0){
			sum += x;
		}
		else{
			int a = *--upper_bound(v.begin(), v.end(), x);
			int b = *lower_bound(v.begin(), v.end(), x);
			if(a == -2147483648){
				sum += abs(b - x);
			}
			else{
				sum += min(abs(a - x), abs(b - x));
			}
		}
		v.insert(upper_bound(v.begin(), v.end(), x), x);
	}
	printf("%d", sum);
	return 0;
}