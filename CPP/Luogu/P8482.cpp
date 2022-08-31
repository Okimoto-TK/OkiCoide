#include <cstdio>
#include <queue>
int a[10000005][2];
int b[10000005][2];
int len[2];
void multi(int x)
{
	int up = 0;
	for(int i = len[x]; i >= 0; i--)
	{
		int th = a[i][x] * 2 + up;
		b[i][x] = th % 10;
		up = th / 10;
	}
}
void divide(int x)
{
	int down = 0;
	for(int i = 1; i <= len[x]; i++)
	{
		a[i][x] += down * 10;
		b[i][x] = a[i][x] / 2;
		if(a[i][x] % 2 == 1) down = 1;
		else down = 0;
	}
}
int c[10];
int main()
{
	int ptr = 0;
	int gtr = 0;
	for(int i = 0; i <= 9; i++)
	{
		scanf("%d", &c[i]);
	}
	for(int i = 9; i >= 0; i--)
	{
		for(int j = 1; j <= c[i]; j++)
		{
			a[++len[ptr > 0]][ptr > 0] = i;
			if(gtr != 1) ptr ^= 1;
			else
			{
				gtr = -1;
			}
		}
		if(gtr == 0 && c[i] % 2 != 0) gtr = 1, ptr = 1;
	}
	int div, mul;
	if(a[len[0]][0] == 0)
	{
		div = 0;
		mul = 1;
	}
	else
	{
		div = 1;
		mul = 0;
	}
	multi(mul);
	divide(div);
	for(int i = b[0][mul] != 0 ? 0 : 1; i <= len[mul]; i++)
	{
		printf("%d", b[i][mul]);
	}
	printf("\n");
	for(int i = b[1][div] != 0 ? 1 : 2; i <= len[div]; i++)
	{
		printf("%d", b[i][div]);
	}
	return 0;
}