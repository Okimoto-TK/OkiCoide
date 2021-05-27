#include <stdio.h>
#include <string.h>
#include <stack>
using namespace std;
char str[1007];
long long f[707][707][3][3];
int t[1007];
int n;
stack <int> St;
const int mod = 1000000007;
void dp(int l, int r)
{
    if(l + 1 == r)
    {
        f[l][r][0][1] = f[l][r][0][2] = f[l][r][1][0] = f[l][r][2][0] = 1;
        return;
    }
    else if(t[l] == r)
    {
        dp(l + 1, r - 1);
        for(int i = 0; i <= 2; i++)
        {
            for(int j = 0; j <= 2; j++)
            {
                if(i != 1)
                {
                    (f[l][r][1][0] += f[l + 1][r - 1][i][j]) %= mod;
                }
                if(j != 1)
                {
                    (f[l][r][0][1] += f[l + 1][r - 1][i][j]) %= mod;
                }
                if(i != 2)
                {
                    (f[l][r][2][0] += f[l + 1][r - 1][i][j]) %= mod;
                }
                if(j != 2)
                {
                    (f[l][r][0][2] += f[l + 1][r - 1][i][j]) %= mod;
                }
            }
        }
    }
    else
    {
        int _r = t[l];
        int _l = t[l] + 1;
        dp(l, _r);
        dp(_l, r);
        for(int i = 0; i <= 2; i++)
        {
            for(int j = 0; j <= 2; j++)
            {
                for(int p = 0; p <= 2; p++)
                {
                    for(int q = 0; q <= 2; q++)
                    {
                        if(j == p && j)
                        {
                            continue;
                        }
                        (f[l][r][i][q] += f[l][_r][i][j] * f[_l][r][p][q]) %= mod;
                    }
                }
            }
        }
    }
}
int main()
{
    scanf("%s", str);
    n = strlen(str);
    for(int i = 0; i < n; i++){
		if(str[i] == '(')
        {
            St.push(i);
        }
		else
        {
            t[St.top()] = i;
            t[i]=St.top();
            St.pop();
        }
	}
    dp(0, n - 1);
    long long ans = 0;
    for(int i = 0; i <= 2; i++)
    {
        for(int j = 0; j <= 2; j++)
        {
            (ans += f[0][n - 1][i][j]) %= mod;
        }
    }
    printf("%lld", ans);
    return 0;
}
