#include <cstdio>
#define N 2000
int n, k;
bool ans[N + 5][N + 5];
int bk[40];
int mid[40];
int len;
int main()
{
	scanf("%d", &k);
	int s = 1, t = 2;
	n = 2;
	while(k)
	{
		bk[len++] = k % 2;
		k >>= 1;
	}
	mid[len] = t;
	for(int i = 1; i <= len - 1; i++)
	{
		mid[i] = ++n;
		if(i > 1)
		{
			ans[mid[i]][mid[i - 1]] = ans[mid[i - 1]][mid[i]] = true;
		}
	}
	if(bk[0] == 1)
	{
		ans[s][mid[1]] = ans[mid[1]][s] = true;
	}
	ans[mid[len - 1]][t] = ans[t][mid[len - 1]] = true;
	int last1, last2;
	last1 = last2 = s;
	for(int j = 1; j <= len - 1; j++)
	{
		++n;
		ans[last1][n] = ans[n][last1] = ans[n][last2] = ans[last2][n] = true;
		++n;
		ans[last1][n] = ans[n][last1] = ans[n][last2] = ans[last2][n] = true;
		last1 = n - 1;
		last2 = n;
		if(j < len - 1 && bk[j] == 1)
		{
			ans[last1][mid[j + 1]] = ans[mid[j + 1]][last1] = ans[last2][mid[j + 1]] = ans[mid[j + 1]][last2] = true;
		}
	}
	ans[t][last1] = ans[last1][t] = ans[last2][t] = ans[t][last2] = true;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			printf("%s", ans[i][j] ? "Y" : "N");
		}
		printf("\n");
	}
	return 0;
}
