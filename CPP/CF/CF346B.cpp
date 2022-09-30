#include <cstdio>
#include <cstring>
#include <string>
#define N 105
int n, m, l;
char s1[N + 5];
char s2[N + 5];
int f[N + 5][N + 5][N + 5];
int g[N + 5][N + 5][N + 5][3];
char h[N + 5][N + 5][N + 5];
char t[N + 5];
int nxt[N + 5];
int main()
{
	scanf("%s", s1 + 1);
	scanf("%s", s2 + 1);
	scanf("%s", t + 1);
	n = strlen(s1 + 1);
	m = strlen(s2 + 1);
	l = strlen(t + 1);
	nxt[1] = 0;
	for(int i = 2; i <= l; i++)
	{
		int x = nxt[i - 1];
		while(x != 0 && t[x + 1] != t[i])
		{
			x = nxt[x];
		}
		if(t[i] == t[x + 1])
		{
			nxt[i] = x + 1;
		}
		else
		{
			nxt[i] = 0;
		}
	}
	memset(f, 128, sizeof(f));
	for(int i = 0; i <= n; i++)
	{
		f[i][0][0] = 0;
	}
	for(int i = 0; i <= m; i++)
	{
		f[0][i][0] = 0;
	}
	for(int i = 0; i <= n; i++)
	{
		for(int j = 0; j <= m; j++)
		{
			for(int k = 0; k < l; k++)
			{
				if(i != n)
				{
					if(f[i][j][k] > f[i + 1][j][k])
					{
						f[i + 1][j][k] = f[i][j][k];
						g[i + 1][j][k][0] = i;
						g[i + 1][j][k][1] = j;
						g[i + 1][j][k][2] = k;
						h[i + 1][j][k] = '\0';
					}
				}
				if(j != m)
				{
					if(f[i][j][k] > f[i][j + 1][k])
					{
						f[i][j + 1][k] = f[i][j][k];
						g[i][j + 1][k][0] = i;
						g[i][j + 1][k][1] = j;
						g[i][j + 1][k][2] = k;
						h[i][j + 1][k] = '\0';
					}
				}
				if(i != n && j != m)
				{
					if(s1[i + 1] == s2[j + 1])
					{
						char c = s1[i + 1];
						int _k = k;
						while(_k != 0 && t[_k + 1] != c)
						{
							_k = nxt[_k];
						}
						if(t[_k + 1] == c)
						{
							_k++;
						}
						if(f[i][j][k] + 1 > f[i + 1][j + 1][_k])
						{
							f[i + 1][j + 1][_k] = f[i][j][k] + 1;
							g[i + 1][j + 1][_k][0] = i;
							g[i + 1][j + 1][_k][1] = j;
							g[i + 1][j + 1][_k][2] = k;
							h[i + 1][j + 1][_k] = c;
						}
					}
				}
			}
		}
	}
	int ans[3] = {0, 0, 0};
	int max = 0;
	for(int i = 0; i < l; i++)
	{
		if(f[n][m][i] > max)
		{
			max = f[n][m][i];
			ans[0] = n;
			ans[1] = m;
			ans[2] = i;
		}
	}
	char out[105];
	out[max + 1] = '\0';
	if(max == 0)
	{
		printf("%d", max);
		return 0;
	}
	else
	{
		while(ans[0] != 0 || ans[1] != 0 || ans[2] != 0)
		{
			int i = ans[0], j = ans[1], k = ans[2];
			if(h[i][j][k] != '\0')
			{
				out[max--] = h[i][j][k];
			}
			ans[0] = g[i][j][k][0];
			ans[1] = g[i][j][k][1];
			ans[2] = g[i][j][k][2];
		}
	}
	printf("%s", out + 1);
	return 0;
}