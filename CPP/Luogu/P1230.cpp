#include <cstdio>
#include <algorithm>
struct Task
{
    int d, w;
} t[505];
int m, n;
bool vis[505];
bool cmp(Task a, Task b)
{
    if(a.w == b.w) return a.d < b.d;
    return a.w > b.w;
}
int main()
{
    scanf("%d%d", &m, &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &t[i].d);
    }
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &t[i].w);
    }
    std::sort(t + 1, t + 1 + n, cmp);
    for(int i = 1; i <= n; i++)
    {
        bool save = false;
        for(int j = t[i].d; j >= 1; j--)
        {
            if(!vis[j])
            {
                save = true;
                vis[j] = true;
                break;
            }
        }
        if(!save) m -= t[i].w;
    }
    printf("%d", m);
    return 0;
}
