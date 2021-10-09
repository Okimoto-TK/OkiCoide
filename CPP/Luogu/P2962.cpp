#include <cstdio>
#include <algorithm>
int n, m;
bool matrix[50][50];
bool x[50];
int min = 0x3f3f3f3f;
void Dfs(int u, int cnt)
{
	if(cnt >= min) return;
	if(u == 0)
	{
		min = std::min(cnt, min);
		return;
	}
	if(matrix[u][u])
	{
		bool ans = matrix[u][n + 1];
		for(int i = u + 1; i <= n; i++) ans ^= (matrix[u][i] & x[i]);
		x[u] = ans;
		Dfs(u - 1, cnt + (x[u] ? 1 : 0));
	}
	else
	{
		bool ans = matrix[u][n + 1];
		for(int i = u + 1; i <= n; i++) ans ^= (matrix[u][i] & x[i]);
		if(ans) return;
		x[u] = true;
		Dfs(u - 1, cnt + 1);
		x[u] = false;
		Dfs(u - 1, cnt);
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		matrix[a][b] = true;
		matrix[b][a] = true;
	}
	for(int i = 1; i <= n; i++)
	{
		matrix[i][i] = true;
		matrix[i][n + 1] = true;
	}
	for(int i = 1; i <= n; i++)
	{
		int ptr = -1;
		for(int j = i; j <= n; j++)
		{
			if(matrix[j][i])
			{
				ptr = j;
				break;
			}
		}
		if(ptr == -1) continue;
		for(int j = 1; j <= n + 1; j++)
		{
			std::swap(matrix[i][j], matrix[ptr][j]);
		}
		for(int j = 1; j <= n; j++)
		{
			if(i == j) continue;
			if(!matrix[j][i]) continue;
			for(int k = 1; k <= n + 1; k++)
			{
				matrix[j][k] ^= matrix[i][k];
			}
		}
	}
	Dfs(n, 0);
	printf("%d", min);
	return 0;
}
