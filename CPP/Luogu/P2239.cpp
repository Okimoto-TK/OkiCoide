#include <stdio.h>
using namespace std;
int n, i, j;
int s[4];
int x = 0;
int y = 0;
int p;
int d[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int abs(int a){
	return a > 0 ? a : -a;
}
int main(int argc, char const *argv[])
{
	scanf("%d%d%d", &n, &i, &j);
	s[0] = n;
	s[1] = n;
	s[2] = -1;
	s[3] = -1;
	for(int k = 1; k <= n * n;){
		if(x != i - 1 && y != j - 1){
			if(p == 0){
				k += s[p] - y - 1;
				y = s[p] - 1;
			}
			else if(p == 2){
				k += y - s[p] - 1;
				y = s[p] + 1;
			}
			else if(p == 1){
				k += s[p] - x - 1;
				x = s[p] - 1;
			}
			else{
				k += x - s[p] - 1;
				x = s[p] + 1;
			}
			s[(p - 1) == -1 ? 3 : p - 1] += ((p - 1) == -1 ? 3 : p - 1) >= 2 ? 1 : -1;
			p ++;
			p %= 4;
		}
		else{
			if(x == i - 1 && y == j - 1){
				printf("%d", k);
				return 0;
			}
			if(p % 2 == 0){
				if(y + d[p][p % 2] == s[p]){
					s[(p - 1) == -1 ? 3 : p - 1] += ((p - 1) == -1 ? 3 : p - 1) >= 2 ? 1 : -1;
					p ++;
					p %= 4;
				}
			}
			else{
				if(x + d[p][p % 2] == s[p]){
					s[(p - 1) == -1 ? 3 : p - 1] += ((p - 1) == -1 ? 3 : p - 1) >= 2 ? 1 : -1;
					p ++;
					p %= 4;
				}
			}
			x += d[p][1];
			y += d[p][0];
			k ++;
		}
	}
	return 0;
}