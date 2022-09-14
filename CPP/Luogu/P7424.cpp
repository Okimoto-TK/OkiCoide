#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#define N 200000
#define SN 470
int n, m, bs, bc;
int L[SN + 5];
int R[SN + 5];
int b[N + 5];
std::vector<int> _b[SN + 5];
int srt[SN + 5][N + 5];
int len[SN + 5];
int ans[N + 5];
struct Sec
{
	int l, r, s;
} a[N + 5];
int count(int k, int x, int y)
{
	return std::upper_bound(srt[k] + 1, srt[k] + 1 + len[k], y) - std::lower_bound(srt[k] + 1, srt[k] + 1 + len[k], x);
}
void solve(int i)
{
	int l = 1, r = bc;
	if(count(bc, a[i].l, a[i].r) < a[i].s) return;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(count(mid, a[i].l, a[i].r) >= a[i].s)
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	//printf("%d\n", l);
	a[i].s -= count(l - 1, a[i].l, a[i].r);
	for(int j = L[l]; j <= R[l]; j++)
	{
		if(b[j] >= a[i].l && b[j] <= a[i].r)
		{
			//printf("%d %d\n", j, a[i].s);
			if(--a[i].s == 0)
			{
				ans[j]++;
				return;
			}
		}
	}
	printf("ERROR!\n");
}
int main()
{
	//freopen("in.in", "r", stdin);
	//freopen("out.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d %d %d", &a[i].l, &a[i].r, &a[i].s);
	}
	bs = ceil(sqrt(m));
	bc = ceil(double(m) / bs);
	for(int i = 1; i <= bc; i++)
	{
		L[i] = R[i - 1] + 1;
		R[i] = std::min(i * bs, m);
		for(int j = L[i]; j <= R[i]; j++)
		{
			scanf("%d", &b[j]);
			_b[i].push_back(b[j]);
		}
		std::sort(_b[i].begin(), _b[i].end());
	}
	for(int i = 1; i <= bc; i++)
	{
		int ptr1 = 1;
		int ptr2 = 1;
		while(ptr1 <= R[i - 1] || ptr2 <= R[i] - L[i] + 1)
		{
			if(ptr2 > R[i] - L[i] + 1)
			{
				srt[i][++len[i]] = srt[i - 1][ptr1];
				ptr1++;
			}
			else if(ptr1 > R[i - 1])
			{
				srt[i][++len[i]] = _b[i][ptr2 - 1];
				ptr2++;
			}
			else
			{
				if(srt[i - 1][ptr1] <= _b[i][ptr2 - 1])
				{
					srt[i][++len[i]] = srt[i - 1][ptr1];
					ptr1++;
				}
				else
				{
					srt[i][++len[i]] = _b[i][ptr2 - 1];
					ptr2++;
				}
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		solve(i);
	}
	for(int i = 1; i <= m; i++)
	{
		printf("%d\n", ans[i]);
	}
	return 0;
}