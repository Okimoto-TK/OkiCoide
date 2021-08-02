#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
int n;
int limit;
int num[30];
bool dfs(int dep, int x)
{
	if(limit < dep || x * (1 << (limit - dep)) < n) return false;
	if(x == n) return true;
	num[dep] = x;
	for(int i = 0; i <= dep; i++)
	{
		if(dfs(dep + 1, x + num[i])) return true;
		if(dfs(dep + 1, x - num[i])) return true;
	}
	return false;
}
int main()
{
	for(scanf("%d", &n); n != 0; scanf("%d", &n))
	{
		for(limit = 0; !dfs(0, 1); limit++);
		printf("%d\n", limit);
	}
	return 0;
}
