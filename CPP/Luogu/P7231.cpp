#include <cstdio>
#include <algorithm>
int n, k;
int p;
int val[4000005];
struct item
{
	int a, b;
} it[8000005];
bool cmp(item x, item y)
{
	return val[x.a] + val[x.b] > val[y.a] + val[y.b];
}
int dot(int x, int y)
{
	return (x - 1) * n + y;
}
bool stk[4000005];
int max = 0;
void dfs(int dep, int last, int sum)
{
	max = std::max(max, sum);
	if(dep > k) return;
	for(int i = last + 1, cnt = 1; i <= p && cnt <= 5; i++)
	{
		if(stk[it[i].a] || stk[it[i].b]) continue;
		stk[it[i].a] = stk[it[i].b] = true;
		dfs(dep + 1, i, sum + val[it[i].a] + val[it[i].b]);
		stk[it[i].a] = stk[it[i].b] = false;
		cnt++;
	} 
}
int main()
{
	long long sum = 0;
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			scanf("%d", &val[dot(i, j)]);
			sum += val[dot(i,j)];
			if(i != 1)
			{
				it[++p].a = dot(i, j);
				it[p].b = dot(i - 1, j);
			}
			if(j != 1)
			{
				it[++p].a = dot(i, j);
				it[p].b = dot(i, j - 1);
				//printf("%d %d\n", dot(i, j), dot(i, j - 1));
			}
		}
	}
	for(int i = 1; i <= p; i++)
	{
	//	printf("%d %d\n", it[i].a, it[i].b);
	}
	std::sort(it + 1, it + 1 + p, cmp);
//	printf("%d %d\n", it[1].a, it[1].b);
	dfs(1, 0, 0);
	printf("%lld", sum - max);
	return 0;
}
