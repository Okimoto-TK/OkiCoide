#include <cstdio>
#include <algorithm>
int T;
int n, r;
double f[300][300];
double p[300];
int d[300];
double pwr[300][300];
double ans[300];
void init()
{
	for(int i = 0; i <= 255; i++)
	{
		p[i] = d[i] = ans[i] = 0;
		for(int j = 0; j <= 255; j++) f[i][j] = pwr[i][j] = 0;
	}
}
double power(int i, int k)
{
	if(pwr[i][k] != 0) return pwr[i][k];
	double r = 1;
	int _k = k;
	double x = 1 - p[i];
	while(k != 0)
	{
		if((k & 1) != 0) r *= x;
		x *= x;
		k >>= 1;
	}
	pwr[i][_k] = r;
	return r;
}
int main()
{
	for(scanf("%d", &T); T != 0; T--)
	{
		init();
		scanf("%d%d", &n, &r);
		for(int i = 1; i <= n; i++) scanf("%lf%d", &p[i], &d[i]);
		f[0][0] = 1;
		for(int i = 1; i <= n; i++)
		{
			for(int j = 0; j <= std::min(i, r); j++)
			{
				if(i != j) f[i][j] += f[i - 1][j] * power(i, r - j);
				if(j > 0) f[i][j] += f[i - 1][j - 1] * (1 - power(i, r - j + 1));
			}
		}
		for(int i = 1; i <= n; i++)
		{
			for(int j = 0; j <= std::min(i - 1, r); j++) ans[i] += f[i - 1][j] * (1 - power(i, r - j));
		}
		double sum = 0;
		for(int i = 1; i <= n; i++) sum += ans[i] * d[i];
		printf("%.10lf\n", sum);
	}
	return 0;
}
