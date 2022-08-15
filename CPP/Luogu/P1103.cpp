#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 105
int n, k;
struct book
{
	int h, b;
} B[N];
bool cmp(book a, book b)
{
	return a.h > b.h;
}
int f[105][105][205];

void dfs(int dep, int rm, int b, bool zero)
{
	if(dep == n)
	{
		if(rm == 1) f[dep][rm][b] = 0;
		else if(rm == 0) f[dep][rm][b] = std::abs(B[dep].b - b);
		return;
	}
	if(f[dep][rm][b] < 0x3f3f3f3f) return;
	dfs(dep + 1, rm - 1, b, zero);
	dfs(dep + 1, rm, B[dep].b, false);
	f[dep][rm][b] = std::min(f[dep + 1][rm - 1][b], f[dep + 1][rm][B[dep].b] + (!zero ? std::abs(B[dep].b - b) : 0));
	f[dep][rm][b] = std::min(0x2f2f2f2f, f[dep][rm][b]);
}
int dp()
{
	memset(f, 0x3f, sizeof(f));
	dfs(1, k, 0, true);
	return f[1][k][0];
}
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", &B[i].h, &B[i].b);
	}
	std::sort(B + 1, B + 1 + n, cmp);
	printf("%d", dp());
	return 0;
}