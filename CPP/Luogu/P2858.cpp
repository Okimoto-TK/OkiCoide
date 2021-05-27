#include <stdio.h>
using namespace std;
int n;
int v[2007];
long long f[2007][2007];
int getMax(int a, int b){ return a > b ? a : b; }
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){ scanf("%d", &v[i]); }
    for(int k = 1; k <= n; k++)
    {
        for(int i = 0; i <= k; i++)
        {
            int j = n - (k - i) + 1;
            if(i){ f[i][j] = getMax(f[i][j], f[i - 1][j] + v[i] * k); }
            if(j != n + 1){ f[i][j] = getMax(f[i][j], f[i][j + 1] + v[j] * k); }
        }
    }
    long long ans = 0;
    for(int i = 0; i <= n; i++)
    {
        int j = i + 1;
        ans = getMax(ans, f[i][j]);
    }
    printf("%lld", ans);
    return 0;
}
