#include <stdio.h>
#include <algorithm>
#include <bitset>
using namespace std;
int t;
int n;
int a[107];
bitset <5000007> f;
int main()
{
    scanf("%d", &t);
    for(int task = 1; task <= t; task++)
    {
        f.reset();
        int ans = 0;
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
        {
            scanf("%d", &a[i]);
        }
        sort(a + 1, a + 1 + n);
        f[0] = true;
        for(int j = 1; j <= n; j++)
        {
            if(!f[a[j]])
            {
                ans++;
            }
            for(int v = a[j]; v <= a[n]; v++)
            {
                f[v] = f[v] | f[v - a[j]];
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
