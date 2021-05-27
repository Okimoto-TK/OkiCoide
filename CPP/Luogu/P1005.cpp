#include <stdio.h>
#include <math.h>
#include <string.h>
using namespace std;
struct num
{
	int n[512];
	int len;
	num(){
		memset(n, 0, sizeof(n));
		len = 0;
	}
	void print(){
		bool zero = true;
		for(int i = len; i > 0; i --){
			if(zero && n[i] == 0)
				continue;
			zero = false;
			printf("%d", n[i]);
		}
		if(zero)
			printf("0");
	}
};
int getMax(int a, int b){
	return a > b ? a : b;
}
num operator + (const num & a, const num & b){
	num c;
	c.len = getMax(a.len, b.len);
	int x = 0;
	for(int i = 1; i <= c.len; i ++){
		c.n[i] = a.n[i] + b.n[i] + x;
		x = c.n[i] / 10;
		c.n[i] %= 10;
	}
	if(x > 0)
		c.n[++ c.len] = x;
	return c;
}
num operator * (const num & a, const int & b){
	num c;
	c.len = a.len;
	int x = 0;
	for(int i = 1; i <= c.len; i ++){
		c.n[i] = a.n[i] * b + x;
		x = c.n[i] / 10;
		c.n[i] %= 10;
	}
	while(x > 0){
		c.n[++ c.len] = x % 10;
		x /= 10;
	}
	return c;
}
num getMax(const num & a, const num & b){
	if(a.len > b.len)
		return a;
	else if(a.len < b.len)
		return b;
	for(int i = a.len; i > 0; i --)
		if(a.n[i] > b.n[i])
			return a;
		else if(a.n[i] < b.n[i])
			return b;
	return a;
}
int n, m;
num ans;
int a[128][128];
num f[128][128];
num gPow[128];
void initPow(){
	gPow[0].n[1] = 1;
	gPow[0].len = 1;
	for(int i = 1; i <= m + 2; i ++)
		gPow[i] = gPow[i - 1] * 2;
}
int main(int argc, char const *argv[])
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
			scanf("%d", &a[i][j]);
	initPow();
	for(int r = 0; r < n; r ++){
		for(int len = 1; len <= m; len ++){
			for(int i = 0; i <= len; i ++){
				if(i == 0){
					f[len][i] = f[len - 1][i] + gPow[len] * a[r][m - len + i];
				}
				else if(i == len){
					f[len][i] = f[len - 1][i - 1] + gPow[len] * a[r][i - 1];
				}
				else{
					f[len][i] = getMax(f[len - 1][i] + gPow[len] * a[r][m - len + i], f[len - 1][i - 1] + gPow[len] * a[r][i - 1]);
				}
			}
		}
		num max;
		for(int i = 0; i <= m; i ++){
			max = getMax(max, f[m][i]);
		}
		ans = ans + max;
	}
	ans.print();
	return 0;
}