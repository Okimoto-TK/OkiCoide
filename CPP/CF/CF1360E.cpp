#include <cstdio>
#include <cstring>
int t, n;
int a[60][60];
int main()
{
	for(scanf("%d", &t); t != 0; t--)
	{
		scanf("%d", &n);
		memset(a, 0, sizeof(a));
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				scanf("%1d", &a[i][j]);
			}
		}
		for(int i = 1; i <= n; i++) a[n + 1][i] = a[i][n + 1] = 1;
		int suc = true;
		for(int i = n; i >= 1; i--)
		{
			for(int j = n; j >= 1; j--)
			{
				if(a[i][j] == 1 && (a[i][j + 1] == 0 && a[i + 1][j] == 0)) suc = false;
			}
		}
		printf("%s\n", suc ? "YES" : "NO");
	}
	return 0;
}
