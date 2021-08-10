#include <cstdio>
#include <algorithm>
int n, m;
int a[20005];
int b[20005];
int ans;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
	std::sort(a + 1, a + 1 + n);
	std::sort(b + 1, b + 1 + m);
	int i, j;
	for(i = 1, j = 1; i <= n && j <= m; j++)
	{
		if(b[j] >= a[i])
		{
			ans += b[j];
			i++;
		}
	}
	if(i <= n && j > m) printf("you died!");
	else printf("%d", ans); 
	return 0;
}
