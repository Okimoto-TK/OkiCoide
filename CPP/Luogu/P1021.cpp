#include <cstdio>
#include <cstring>
#include <algorithm>
int n, k;
int stk[15];
int out[15];
int ans;
int val[15][300000];
void dfs(int dep, int maxn)
{
	if(dep == k)
	{
		if(maxn > ans) memcpy(out, stk, sizeof(out));
		ans = std::max(maxn, ans);
		return;
	}
	for(int i = stk[dep - 1] + 1; i <= maxn + 1; i++)
	{
		stk[dep] = i;
		int j;
		for(j = 1; j <= i * n; j++)
		{
			bool suc = false;
			val[dep][j] = 0x3f3f3f3f;
			for(int _k = 0; _k <= dep && stk[_k] <= j; _k++)
			{
				if(val[dep][j - stk[_k]] < n)
				{
					val[dep][j] = std::min(val[dep][j], val[dep][j - stk[_k]] + 1);
					suc = true;
				}
			}
			if(!suc) break;
		}
		dfs(dep + 1, j - 1);
	}
}
int main()
{
	scanf("%d%d", &n, &k);
	stk[0] = 1;
	for(int i = 1; i <= n; i++)
	{
		val[0][i] = i;
	}
	dfs(1, n);
	for(int i = 0; i < k; i++) printf("%d ", out[i]);
	printf("\nMAX=%d", ans);
	return 0;
}

