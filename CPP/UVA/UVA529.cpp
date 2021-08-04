#include <cstdio>
int n;
int cnt[100];
int pwr[100];
bool dfs(int limit, int dep, int x)
{
	if(x == n) return true;
	if(dep > limit) return false;
	if(x << (limit - dep + 1) < n) { return false; }
	for(int i = 1; i < dep; i++)
	{
		for(int j = i; j < dep; j++)
		{
			cnt[dep] = cnt[i] + cnt[j];
			if(dfs(limit, dep + 1, cnt[dep])) return true;
		}
	}
	return false;
}
int main()
{
	for(scanf("%d", &n); n != 0; scanf("%d", &n))
	{
		if(n == 1)
		{
			printf("1\n");
			continue;
		}
		cnt[1] = 1;
		int limit = 2;
		while(!dfs(limit, 2, 1)) limit++;
		for(int i = 1; i <= limit; i++)
		{
			printf("%d", cnt[i]);
			if(i != limit) putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}
