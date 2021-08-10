#include <cstdio>
int n;
int cnt;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int tmp;
		scanf("%d", &tmp);
		cnt ^= tmp;
	}
	printf("%d", cnt);
	return 0;
}
