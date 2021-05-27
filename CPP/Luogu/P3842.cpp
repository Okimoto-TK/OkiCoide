#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;
struct seg
{
    int l;
    int r;
};
int n;
seg a[20007];
int f[20007][2];
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d%d", &a[i].l, &a[i].r);
    }
    a[0].l = 1;
    a[0].r = 1;
    a[n].r = n;
    f[0][0] = -1;
    f[0][1] = -1;
    for(int i = 1; i <= n; i++)
    {
        f[i][0] = 1 + min(f[i - 1][1] + abs(a[i].r - a[i].l) + abs(a[i].r - a[i - 1].r), f[i - 1][0] + abs(a[i].r - a[i].l) + abs(a[i].r - a[i - 1].l));
        f[i][1] = 1 + min(f[i - 1][1] + abs(a[i].r - a[i].l) + abs(a[i].l - a[i - 1].r), f[i - 1][0] + abs(a[i].r - a[i].l) + abs(a[i].l - a[i - 1].l));
    }
    printf("%d", f[n][1]);
    return 0;
}
