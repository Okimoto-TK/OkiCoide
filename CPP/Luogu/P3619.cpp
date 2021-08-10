#include <cstdio>
#include <algorithm>
int z;
int n, T;
struct task
{
	int t, b;
};
task a[100005];
task a1[100005];
task a2[100005];
int cnt1;
int cnt2;
bool cmp1(task x, task y)
{
	return x.t < y.t;
}
bool cmp2(task x, task y)
{
	return x.t + x.b > y.t + y.b;
}
int main()
{
	for(scanf("%d", &z); z != 0; z--)
	{
		cnt1 = 0;
		cnt2 = 0;
		scanf("%d%d", &n, &T);
		for(int i = 1; i <= n; i++)
		{
			scanf("%d%d", &a[i].t, &a[i].b);
			if(a[i].b >= 0)
			{
				a1[++cnt1].t = a[i].t;
				a1[cnt1].b = a[i].b;
			}
			else
			{
				a2[++cnt2].t = a[i].t;
				a2[cnt2].b = a[i].b;
			}
		}
		std::sort(a1 + 1, a1 + 1 + cnt1, cmp1);
		for(int i = 1; i <= cnt1; i++)
		{
			if(T > a1[i].t) T += a1[i].b;
			else
			{
				printf("-1s\n");
				goto endup;
			}
		}
		std::sort(a2 + 1, a2 + 1 + cnt2, cmp2);
		for(int i = 1; i <= cnt2; i++)
		{
			if(T > a2[i].t) T += a2[i].b;
			else
			{
				printf("-1s\n");
				goto endup;
			}
			if(T <= 0)
			{
				printf("-1s\n");
				goto endup;
			}
		}
		printf("+1s\n");
endup:
		continue;
	}
	return 0;
}
