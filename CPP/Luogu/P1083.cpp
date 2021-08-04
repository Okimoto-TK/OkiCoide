#include <cstdio>
#include <cstring>
int n, m;
int r[1000005];
int d[1000005];
int s[1000005];
int t[1000005];
int diff[1000005];
bool check(int x)
{
	memset(diff, 0, sizeof(diff));
	for(int i = 1; i <= x; i++)
	{
		diff[s[i]] += d[i];
		diff[t[i] + 1] -= d[i];
	}
	int tmp = 0;
	for(int i = 1; i <= n; i++)
	{
		tmp += diff[i];
		if(tmp > r[i]) return true;
	}
	return false;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &r[i]);
	}
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &d[i], &s[i], &t[i]);
	}
	int l = 1;
	int r = m + 1;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(check(mid))
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	if(l == m + 1) printf("0");
	else printf("-1\n%d", l);
	return 0;
}
