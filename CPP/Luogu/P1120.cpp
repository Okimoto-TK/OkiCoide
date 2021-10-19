#include <cstdio>
#include <cstring>
#include <algorithm>
int n;
int a[100];
int vis[100];
int nxt[100];
bool dfs(int cur, int sum, int lower, int lim)
{
	if(cur == n) return sum == 0;
	if(sum == 0)
	{
		int i = 1;
		for(; i <= n; i++)
		{
			if(!vis[i]) break;
		}
		vis[i] = true;
		if(dfs(cur + 1, a[i] % lim, i, lim)) return true;
		vis[i] = false;
		return false;
	}
	int l = lower + 1, r = n;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(a[mid] > lim - sum) l = mid + 1;
		else r = mid;
	}
	for(int i = l; i <= n; i++)
	{
		if(vis[i]) continue;
		vis[i] = true;
		if(dfs(cur + 1, (sum + a[i]) == lim ? 0 : sum + a[i], i, lim)) return true;
		vis[i] = false;
		if(lim - sum == a[i]) return false;
		i = nxt[i];
	}
	return false;
}
bool cmp(int a, int b) { return a > b; }
int main()
{
	scanf("%d", &n);
	memset(vis, 0, sizeof(vis));
	int lower = -0x3f3f3f3f, sum = 0, cnt = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		if(a[i] > 50)
		{
			a[i] = 0;
			cnt++;
		}
		lower = std::max(lower, a[i]);
		sum += a[i];
	}
	std::sort(a + 1, a + 1 + n, cmp);
	n -= cnt;
	nxt[n] = n;
	for(int i = n - 1; i >= 1; i--)
	{
		if(a[i] == a[i + 1]) nxt[i] = nxt[i + 1];
		else nxt[i] = i;
	}
	for(int i = lower; i <= sum; i++)
	{
		if((sum % i) != 0) continue;
		if(dfs(0, 0, 0, i))
		{
			printf("%d\n", i);
			break;
		}
	}
	return 0;
}
