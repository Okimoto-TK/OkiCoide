#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int n, m;
unsigned short f[5][41][41][41][41];
unsigned short a[351];
int t[5];
const int inf = 0xbfbf;
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= m; i++)
    {
        int b;
        scanf("%d", &b);
        t[b]++;
    }
    f[1][t[1]][t[2]][t[3]][t[4]] = a[1];
    for(int i = 2; i <= n; i++)
    {
        for(int t1 = 0; t1 <= t[1]; t1++)
        {
            for(int t2 = 0; t2 <= t[2]; t2++)
            {
                for(int t3 = 0; t3 <= t[3]; t3++)
                {
                    for(int t4 = 0; t4 <= t[4]; t4++)
                    {
                        f[i % 5][t1][t2][t3][t4] = inf;
                        bool v = false;
                        if(i - 1 >= 1 && t1 != t[1] && f[(i % 5 + 4) % 5][t1 + 1][t2][t3][t4] != inf)
                        {
                            f[i % 5][t1][t2][t3][t4] = (v) ? max(f[(i % 5 + 4) % 5][t1 + 1][t2][t3][t4] + a[i], (int)f[i % 5][t1][t2][t3][t4]) : (f[(i % 5 + 4) % 5][t1 + 1][t2][t3][t4] + a[i]);
                            v = true;
                        }
                        if(i - 2 >= 1 && t2 != t[2] && f[(i % 5 + 3) % 5][t1][t2 + 1][t3][t4] != inf)
                        {
                            f[i % 5][t1][t2][t3][t4] = (v) ? max(f[(i % 5 + 3) % 5][t1][t2 + 1][t3][t4] + a[i], (int)f[i % 5][t1][t2][t3][t4]) : (f[(i % 5 + 3) % 5][t1][t2 + 1][t3][t4] + a[i]);
                            v = true;
                        }
                        if(i - 3 >= 1 && t3 != t[3] && f[(i % 5 + 2) % 5][t1][t2][t3 + 1][t4] != inf)
                        {
                            f[i % 5][t1][t2][t3][t4] = (v) ? max(f[(i % 5 + 2) % 5][t1][t2][t3 + 1][t4] + a[i], (int)f[i % 5][t1][t2][t3][t4]) : (f[(i % 5 + 2) % 5][t1][t2][t3 + 1][t4] + a[i]);
                            v = true;
                        }
                        if(i - 4 >= 1 && t4 != t[4] && f[(i % 5 + 1) % 5][t1][t2][t3][t4 + 1] != inf)
                        {
                            f[i % 5][t1][t2][t3][t4] = (v) ? max(f[(i % 5 + 1) % 5][t1][t2][t3][t4 + 1] + a[i], (int)f[i % 5][t1][t2][t3][t4]) : (f[(i % 5 + 1) % 5][t1][t2][t3][t4 + 1] + a[i]);
                            v = true;
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for(int t1 = 0; t1 <= t[1]; t1++)
    {
        for(int t2 = 0; t2 <= t[2]; t2++)
        {
            for(int t3 = 0; t3 <= t[3]; t3++)
            {
                for(int t4 = 0; t4 <= t[4]; t4++)
                {
                    if(f[n % 5][t1][t2][t3][t4] < inf)
                    {
                        ans = max((int)f[n % 5][t1][t2][t3][t4], ans);
                    }
                }
            }
        }
    }
    printf("%d", ans);
    return 0;
}
