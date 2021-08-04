#include <cstdio>
int n, q;
char str[100005];
int sum[100005];
int main()
{
	scanf("%d%d", &n, &q);
	scanf("%s", str + 1);
	for(int i = 1; i <= n; i++) sum[i] = sum[i - 1] + str[i] - 'a' + 1;
	for(int i = 1; i <= q; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", sum[r] - sum[l - 1]);
	}
	return 0;
}
