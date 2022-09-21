#include <cstdio>
int n, m;
int ans[5005];
int main()
{
	scanf("%d%d", &n, &m);
	ans[1] = 1;
	ans[2] = 2;
	int i;
	for(i = 3; i <= n && m > 0; i++)
	{
		if((i - 1) / 2 > m)
		{
			int j = (i - 1) - 2 * m + 1;
			ans[i] = i + j - 1;
			m = 0;
		}
		else
		{
			m -= (i - 1) / 2;
			ans[i] = i;
		}
	}
	i--;
	if(m > 0)
	{
		printf("-1");
		return 0;
	}
	int val = 1e9;
	for(int j = n; j > i; j--)
	{
		ans[j] = val;
		val -= ans[i - 1] + ans[i] + 1;
	}
	for(int i = 1; i <= n; i++)
	{
		printf("%d ", ans[i]);
	}
	return 0;
}
