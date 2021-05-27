#include <stdio.h>
#include <string.h>
using namespace std;
int n;
const int MOD = 998244353;
int h[20001];
int f[20001];
int s[20001];
int getMax(int a, int b){
	return a > b ? a : b;
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	int v = 0;
	for(int i = 0; i < n; i ++){
		scanf("%d", &h[i]);
		v = getMax(v, h[i]);
	}
	int ans = n;
	for(int i = -1 * v; i <= v; i ++){
		memset(s, 0, sizeof(s));
		memset(f, 0, sizeof(f));
		for(int j = 0; j < n; j ++){
			if(h[j] - i >= 0 && h[j] - i <= 20000){
				f[j] += s[h[j] - i];
				s[h[j]] += f[j] + 1;
				s[h[j]] %= MOD;
				f[j] %= MOD;
			}
			else
				s[h[j]] ++;
			ans += f[j];
			ans %= MOD;
		}
	}
	printf("%d", ans);
	return 0;
}