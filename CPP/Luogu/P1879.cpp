#include <stdio.h>
#include <bitset>
#include <algorithm>
using namespace std;
const int mod = 100000000;
int m, n, p;
int plc[20];
int s[5007];
long long f[20][5007];
bool check(int bin)
{
    bitset<12> buf(bin);
    for(int i = 0; i < n; i++)
    {
        if(buf[i])
        {
            if(i + 1 < n && buf[i + 1])
            {
                return false;
            }
        }
    }
    return true;
}
int main()
{
    scanf("%d%d", &m, &n);
    for(int bin = 0; bin < 1 << n; bin++)
    {
        if(check(bin))
        {
            s[p++] = bin;
        }
    }
    for(int i = 1; i <= m; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            int is;
            scanf("%d", &is);
            plc[i] |= is ? (1 << (j - 1)) : 0;
        }
    }
    f[0][0] = 1;
    for(int l = 1; l <= m; l++)
    {
        for(int i = 0; i < p; i++)
        {
            int bin_i = s[i];
            if((bin_i | plc[l]) != plc[l])
            {
                continue;
            }
            for(int j = 0; j < p; j++)
            {
                int bin_j = s[j];
                if((bin_j | plc[l - 1]) != plc[l - 1])
                {
                    continue;
                }
                if((bin_i & bin_j) != 0)
                {
                    continue;
                }
                (f[l][i] += f[l - 1][j]) %= mod;
            }
        }
    }
    long long ans = 0;
    for(int i = 0; i < p; i++)
    {
        (ans += f[m][i]) %= mod;
    }
    printf("%lld", ans);
    return 0;
}
