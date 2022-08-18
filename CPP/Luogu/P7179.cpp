#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 500
int n, m, k;
long long f[N + 5][N + 5][2][2][2][2];
long long p2(long long x)
{
	return x * x;
}
long long dfs(int len, int wid, int left, int right, int up, int down)
{
	if(f[len][wid][up][down][left][right] != -1) return f[len][wid][up][down][left][right];
	long long r = p2(len * wid - k);
	if(left || right || (up && down))
	{
		for(int i = 1; i < wid; i++)
		{
			r = std::min(r, dfs(len, wid - i, left, right, up, 0) + dfs(len, i, left, right, 0, down));
		}
	}
	if(up || down || (left && right))
	{
		for(int i = 1; i < len; i++)
		{
			r = std::min(r, dfs(len - i, wid, left, 0, up, down) + dfs(i, wid, 0, right, up, down));
		}
	}
	return f[len][wid][up][down][left][right] = r;
}
int main()
{
	memset(f, -1, sizeof(f));
	scanf("%d%d%d", &n, &m, &k);
	printf("%lld", dfs(n, m, 1, 1, 1, 1));

	return 0;
}