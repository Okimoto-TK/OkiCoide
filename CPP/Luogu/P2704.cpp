#include <stdio.h>
#include <bitset>
#include <algorithm>
#include <string.h>
using namespace std;
int n, m, p;
int plc[107];
int f[107][507][507];
int s[1007];
bool check(int bin)
{
    bitset<10> buf(bin);
    for(int i = 0; i < m; i++)
    {
        if(buf[i])
        {
            if(i + 1 < m && buf[i + 1])
            {
                return false;
            }
            if(i + 2 < m && buf[i + 2])
            {
                return false;
            }
        }
    }
    return true;
}
int count(int bin)
{
    int r = 0;
    for(; bin; r++)
    {
        bin &= (bin - 1);
    }
    return r;
}
int main()
{
    memset(f, -128 / 2, sizeof(f));
    f[0][0][0] = 0;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < 1 << m; i++)
    {
        if(check(i))
        {
            s[p++] = i;
        }
    }
    for(int i = 1; i <= n; i++)
    {
        char buf[16];
        scanf("%s", buf);
        for(int j = 1; j <= m; j++)
        {
            plc[i] |= (buf[j - 1] == 'P') ? (1 << (j - 1)) : 0;
        }
    }
    for(int l = 1; l <= n; l++)
    {
        for(int i = 0; i < p; i++)
        {
            int bin = s[i];
            if((bin | plc[l]) != plc[l])
            {
                continue;
            }
            for(int j = 0; j < p; j++)
            {
                int _bin = s[j];
                if((_bin | plc[l - 1]) != plc[l - 1])
                {
                    continue;
                }
                if(bin & _bin)
                {
                    continue;
                }
                for(int k = 0; k < p; k++)
                {
                    int __bin = s[k];
                    if((__bin | plc[l - 2]) != plc[l - 2])
                    {
                        continue;
                    }
                    if(bin & __bin)
                    {
                        continue;
                    }
                    f[l][i][j] = max(f[l][i][j], f[l - 1][j][k]);
                }
                f[l][i][j] += count(bin);
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < p; i++)
    {
        for(int j = 0; j < p; j++)
        {
            ans = max(ans, f[n][i][j]);
        }
    }
    printf("%d", ans);
    return 0;
}
