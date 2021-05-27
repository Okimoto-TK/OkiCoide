#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
int n;
int a[107];
int f[107];
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= n; i++)
    {
        f[i] = a[i] + f[i - 1];
        for(int j = 1; j < i; j++)
        {
            f[i] = max(f[i], f[j - 1] + abs(a[i] - a[j]) * (i - j + 1));
        }
    }
    printf("%d", f[n]);
    return 0;
}
