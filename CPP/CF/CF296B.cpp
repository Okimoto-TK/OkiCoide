#include <cstdio>
const int mod = 1000000007;
int n;
char s[100005];
char w[100005];
int f[100005][2][2];
int main()
{
	scanf("%d", &n);
	scanf("%s", s + 1);
	scanf("%s", w + 1);
	f[0][0][0] = 1;
	for(int i = 1; i <= n; i++)
	{
		for(int a = (s[i] == '?' ? 0 : s[i] - '0'); a <= (s[i] == '?' ? 9 : s[i] - '0'); a++)
		{
			for(int b = (w[i] == '?' ? 0 : w[i] - '0'); b <= (w[i] == '?' ? 9 : w[i] - '0'); b++)
			{
				for(int x = 0; x <= 1; x++)
				{
					for(int y = 0; y <= 1; y++)
					{
						(f[i][x | (a > b)][y | (a < b)] += f[i - 1][x][y]) %= mod;
					}
				}			
			}
		}
	}
	printf("%d", f[n][1][1]);
	return 0;
}
