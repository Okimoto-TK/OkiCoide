#include <stdio.h>
using namespace std;
int m;
int d;
int ans;
const int Day[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int main(int argc, char const *argv[])
{
	scanf("%d-%d", &m, &d);
	if(m < 1 || m > 12){
		if(m / 10 <= 1){
			ans += 1;
			m = 12;
		}
		else{
			ans += 1;
			m %= 10 + 1;
			if(m == 0)
				m = 10;
		}
	}
	if(d == 0 || d > Day[m]){
		ans ++;
	}
	printf("%d", ans);
	return 0;
}