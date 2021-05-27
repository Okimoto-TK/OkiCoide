#include <stdio.h>
#include <algorithm>
using namespace std;
int h1, h2, m1, m2, n, v;
int p[10007];
int t[10007];
int c[10007];
int f[1007];
int main()
{
    scanf("%d:%d %d:%d %d", &h1, &m1, &h2, &m2, &n);
    int v = (h2 - h1) * 60 + m2 - m1;
    for(int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &t[i], &c[i], &p[i]);
    }
    for(int i = 1; i <= n; i++)
    {
        if(p[i] == 0)
        {
            for(int j = t[i]; j <= v; j++)
            {
                f[j] = max(f[j], f[j - t[i]] + c[i]);
            }
        }
        else
        {
            for(int j = v; j >= t[i]; j--)
            {
                for(int k = 1; k <= p[i] && j >= k * t[i]; k++)
                {
                    f[j] = max(f[j], f[j - k * t[i]] + c[i] * k);
                }
            }
        }
    }
    printf("%d", f[v]);
    return 0;
}
