#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <map>
int k, n, m;
const long long max = 0x3f3f3f3f3f3f3f3f;
int reb[600][600];
long long f[2][520][520];
long long g[520][520];
inline int read()
{
    int m=0,n=1; 
	char ch;
	ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')
	{
	    m=m*10+ch-'0';
	    ch=getchar();
	}
    return m*n;
}
void solve(int dep, int l, int r)
{
	int d = dep&1;
	if(dep == k)
	{
		f[d][l][r] = f[d][r][l] = reb[l][r];
		return;
	}
	int mid = (l + r) >> 1;
	int lmid = (l + mid) >> 1;
	int rmid = (mid + 1 + r) >> 1;
	solve(dep + 1, l, mid);
	solve(dep + 1, mid + 1, r);
	for(int i = l; i <= mid; i++)
	{
		for(int j = mid + 1; j <= r; j++)
		{
			f[d][i][j] = max;
			g[i][j] = g[j][i] = max;
		}
		for(register int x = (i <= lmid ? lmid + 1 : l); x <= (i <= lmid ? mid : lmid); x++)
		{
			for(register int y = mid + 1; y <= r; y++)
			{
				g[i][y] = std::min(g[i][y], f[d^1][i][x] + reb[x][y]);
			}
		}
	}
	for(register int i = l; i <= mid; i++)
	{
		for(register int j = mid + 1; j <= r; j++)
		{
				for(register int y = (j <= rmid ? rmid + 1 : mid + 1); y <= (j <= rmid ? r : rmid); y++)
				{
					f[d][i][j] = f[d][j][i] = std::min(f[d][i][j], f[(d)^1][y][j] + g[i][y]);
				}
		}
	}
}
int main()
{
	k = read();
	memset(f, 0x3f, sizeof(f)); 
	n = 1 << k;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			reb[i][j] = read();
		}
	}
	m = pow(2, k - 1);
	solve(1, 1, n);
	long long ans = 0x3f3f3f3f3f3f3f3f;
	int mid = (1 + n) >> 1;
	for(int i = 1; i <= mid; i++)
	{
		for(int j = mid + 1; j <= n; j++)
		{
			ans = std::min(ans, f[1][i][j]);
		}
	}
	printf("%lld", ans);
	return 0;
}
