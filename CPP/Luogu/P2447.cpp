#include <cstdio>
#include <algorithm>
#include <bitset>
int n, m;
std::bitset<1005> a[2005];
bool cmp(int c, int x, int y)
{
	return a[x][c] > a[y][c];
}
int min;
int x[1005];
int gauss()
{
	int r, c;
	for(r = 1, c = 1; c <= n; c++, r++)
	{
		int max = r;
		for(int i = r + 1; i <= m; i++)
		{
			if(cmp(c, i, max))
			{
				max = i;
			}
		}
		min = std::max(min, max);
		if(max != r) std::swap(a[max], a[r]);
		if(!a[r][c])
		{
			r--;
			continue;
		}
		for(int i = r + 1; i <= m; i++)
		{
			if(!a[i][c]) continue;
			a[i] ^= a[r];
		}
	}
	if(n + 1 - r > 0)
	{
		return -1;
	}
	for(int i = n; i >= 1; i--)
	{
		for(int j = i + 1; j <= n; j++)
		{
			a[i][n + 1] = (a[i][j] & x[j]) ^ a[i][n + 1];
		}
		x[i] = a[i][n + 1];
	}
	return 0;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		for(int j = 1; j <= n + 1; j++)
		{
			int v;
			scanf("%1d", &v);
			a[i][j] = v;
		}
	}
	if(gauss() == -1)
	{
		printf("Cannot Determine");
	}
	else
	{
		printf("%d\n", min);
		for(int i = 1; i <= n; i++)
		{
			printf("%s\n", x[i] == 1 ? "?y7M#" : "Earth");
		}
	}
	return 0;
}