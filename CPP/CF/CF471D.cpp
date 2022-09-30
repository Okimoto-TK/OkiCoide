#include <cstdio>
#define N 200000
int n, w;
int a[N + 5];
int b[N + 5];
int s[N + 5];
int t[N + 5];
int nxt[N + 5];
int main()
{
	scanf("%d%d", &n, &w);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		if(i >= 1) s[i - 1] = a[i] - a[i - 1];
	}
	for(int i = 1; i <= w; i++)
	{
		scanf("%d", &b[i]);
		if(i >= 1) t[i - 1] = b[i] - b[i - 1];
	}
	nxt[1] = 0;
	for(int i = 1, j = 0; i < w;)
	{
		if(j == 0 || t[i] == t[j])
		{
			i++;
			j++;
			nxt[i] = j;
		}
		else
		{
			j = nxt[j];
		}
	}
	int cnt = 0;
	for(int i = 1, j = 1; i <= n;)
	{
		//printf("%d %d\n", s[i], t[j]);
		if(j == w)
		{
			cnt++;
			j = nxt[j];
		}
		else if(j == 0 || s[i] == t[j])
		{
			i++, j++;
		}
		else
		{
			j = nxt[j];
		}
	}
	printf("%d", cnt);
	return 0;
}
