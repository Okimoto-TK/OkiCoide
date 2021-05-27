#include <stdio.h>
#include <algorithm>
using namespace std;
int n, ans = 0x3f3f3f3f;
int set[200007];
int dis[200007];
int find(int x)
{
    if(set[x] == x)
    {
        return x;
    }
    int spr = set[x];
    set[x] = find(set[x]);
    dis[x] += dis[spr];
    return set[x];
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        set[i] = i;
    }
    for(int u = 1; u <= n; u++)
    {
        int v;
        scanf("%d", &v);
        int su = find(u);
        int sv = find(v);
        if(su == sv)
        {
            ans = min(ans, dis[u] + dis[v] + 1);
        }
        else
        {
            set[su] = sv;
            dis[u] = dis[v] + 1;
        }
    }
    printf("%d", ans);
    return 0;
}
