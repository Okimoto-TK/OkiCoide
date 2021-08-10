#include <cstdio>
#include <cstring>
#include <algorithm>
int n, m;
int a[100];
int backup[100];
int total;
int b[2000];
int sum[2000];
bool check(int x, int dep, int waste, int p)
{
	if(total - waste < sum[x]) return false;
	if(dep == 0) return true;
	for(int i = p; i <= n; i++)
	{
		bool wasting = false;
		if(a[i] < b[dep]) continue;
		a[i] -= b[dep];
		if(a[i] < b[1]) wasting = true;
		if(check(x, dep - 1, waste + (wasting ? a[i] : 0), b[dep] == b[dep - 1] ? i : 1)) return true;
		a[i] += b[dep];
	}
	return false;
}
bool cmp(int x, int y)
{
	return x < y;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		total += a[i];
	}
	scanf("%d", &m);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d", &b[i]);
	}
	std::sort(b + 1, b + 1 + m, cmp);
	int l = 0;
	int r = m;
	for(int i = 1; i <= m; i++)
	{
		sum[i] = sum[i - 1] + b[i];
		if(sum[i] > total)
		{
			r = i - 1;
			break;
		}
	}
	for(int i = 1; i <= n; i++) backup[i] = a[i];
	int waste = 0;
	for(int i = 1; i <= n; i++)
	{
		if(a[i] < b[1]) waste += a[i];
	}
	while(l < r)
	{
		int mid = (l + r + 1) >> 1;
		for(int i = 1; i <= n; i++) a[i] = backup[i];
		if(check(mid, mid, waste, 1)) l = mid;
		else r = mid - 1;
	}
	printf("%d", l);
	return 0;
}
