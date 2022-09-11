#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define N 10000
struct INT
{
	int d[5000];
	int len;
	INT()
	{
		memset(d, 0, sizeof(d));
		len = 0;
	}
	void operator+=(const INT & A)
	{
		len = std::max(len, A.len);
		int u = 0;
		for(int i = 1; i <= len; i++)
		{
			d[i] += u + A.d[i];
			u = d[i] / 10;
			d[i] %= 10;
		}
		while(u != 0)
		{
			d[++len] = u % 10;
			u /= 10;
		}
	}
	void operator*=(const int & x)
	{
		int u = 0;
		for(int i = 1; i <= len; i++)
		{
			d[i] = d[i] * x + u;
			u = d[i] / 10;
			d[i] %= 10;
		}
		while(u != 0)
		{
			d[++len] = u % 10;
			u /= 10;
		}
	}
	void operator/=(const int & x)
	{
		int r = 0;
		for(int i = len; i >= 1; i--)
		{
			r *= 10;
			r += d[i];
			d[i] = r / x;
			r %= x;
		}
		while(!d[len])
		{
			len--;
		}
	}
	void print()
	{
		int _len = std::min(len, 100);
		while(!d[_len])
		{
			_len--;
		}
		for(int i = _len; i >= 1; i--)
		{
			printf("%d", d[i]);
		}
	}
};
int n;
int cnt[N + 5];
int fac[N + 5];
int main()
{
	while(scanf("%d", &n) != EOF)
	{
		memset(cnt, 0, sizeof(cnt));
		fac[n + 1] = 0;
		INT Ans;
		Ans.len = 1;
		Ans.d[1] = 1;
		INT Tmp;
		Tmp.len = 1;
		Tmp.d[1] = 1;
		for(int i = 1; i <= n / 2; i++)
		{
			int a = n - 2 * i + 1;
			int b = n - 2 * i + 2;
			int c = i + 1;
			int d = i;
			Tmp *= a;
			Tmp *= b;
			Tmp /= c;
			Tmp /= d;
			Ans += Tmp;
		}
		Ans.print();
		putchar('\n');
	}
}