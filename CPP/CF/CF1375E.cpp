#include <cstdio>
#include <algorithm>
int a[1005];
int pos[1005];
struct item
{
	int v, id;
} b[1005];
int n;
bool cmp(item x, item y)
{
	if(x.v == y.v) return x.id < y.id;
	return x.v < y.v;
}
void swap(int x, int y)
{
	pos[a[x]] = y;
	pos[a[y]] = x;
	std::swap(a[x], a[y]);
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		b[i].v = a[i];
		b[i].id = i;
	}
	std::sort(b + 1, b + 1 + n, cmp);
	for(int i = 1; i <= n; i++)
	{
		a[b[i].id] = i;
	}
	int cnt = 0;
	for(int i = 1; i <= n; i++)
	{
		pos[a[i]] = i;
		for(int j = 1; j < i; j++)
		{
			cnt += (a[j] > a[i]);
		}
	}
	printf("%d\n", cnt);
	for(int i = n; i >= 1; i--)
	{
		for(int j = a[i] + 1; j <= i; j++)
		{
			printf("%d %d\n", pos[j], i);
			swap(pos[j], i);
		}
	}
	return 0;
}
