#include <cstdio>
#include <algorithm>
int n, h1, h2;
int a[1005];
int b[1005];
int s1[1005];
int s2[1005];
bool cmp1(int p1, int p2)
{
    return a[p1] < a[p2];
}
bool cmp2(int p1, int p2)
{
    return b[p1] > b[p2];
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &b[i]);
    }
    for(int i = 1; i <= n; i++)
    {
        if(a[i] < b[i]) s1[++h1] = i;
        else s2[++h2] = i;
    }
    std::sort(s1 + 1, s1 + 1 + h1, cmp1);
    std::sort(s2 + 1, s2 + 1 + h2, cmp2);
    int atick, btick;
    atick = btick = 0;
    for(int i = 1; i <= h1; i++)
    {
        atick += a[s1[i]];
        btick = std::max(atick, btick) + b[s1[i]];
    }
    for(int i = 1; i <= h2; i++)
    {
        atick += a[s2[i]];
        btick = std::max(atick, btick) + b[s2[i]];
    }
    printf("%d\n", btick);
    for(int i = 1; i <= h1; i++)
    {
        printf("%d ", s1[i]);
    }
    for(int i = 1; i <= h2; i++)
    {
        printf("%d ", s2[i]);
    }
    return 0;
}
