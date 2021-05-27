#include <stdio.h>
#include <string>
#include <bitset>
using namespace std;
int n, k;
int count(int x)
{
    int r = 0;
    bool l = false;
    for(int i = 0; i < n; i++)
    {
        if(x & (1 << i))
        {
            r++;
            if(l)
            {
                return -1;
            }
            l = true;
        }
        else
        {
            l = false;
        }
    }
    return r;
}
bool match(int x, int y)
{
    bitset<10> a(x);
    bitset<10> b(y);
    for(int i = 0; i < n; i++)
    {
        if(a[i])
        {
            if(i != 0 && b[i - 1])
            {
                return false;
            }
            if(b[i])
            {
                return false;
            }
            if(i != n - 1 && b[i + 1])
            {
                return false;
            }
        }
    }
    return true;
}
long long b[10][100][2007];
int main()
{
    scanf("%d%d", &n, &k);
    b[0][0][0] = 1;
    for(int i = 1; i <= n; i++)
    {
        for(int bin = 0; bin < 1 << n; bin++)
        {
            int cnt = count(bin);
            if(cnt == -1)
            {
                continue;
            }
            for(int _bin = 0; _bin < 1 << n; _bin++)
            {
                if(count(_bin) == -1)
                {
                    continue;
                }
                if(match(bin, _bin))
                {
                    for(int j = cnt; j <= k; j++)
                    {
                        b[i][j][bin] += b[i - 1][j - cnt][_bin];
                    }
                }
            }
        }
    }
    unsigned long long ans = 0;
    for(int i = 0; i < 1 << n; i++)
    {
        ans += b[n][k][i];
    }
    printf("%llu", ans);
    return 0;
}
