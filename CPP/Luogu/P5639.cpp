#include <cstdio>
int n;
int a[1000005];
int cnt;
int main()
{
	scanf("%d", &n);
	a[0] = 1;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		if(a[i] != a[i - 1]) cnt++;
	}
	printf("%d", cnt);
	return 0;
}
