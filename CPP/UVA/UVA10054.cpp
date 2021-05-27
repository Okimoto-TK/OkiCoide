#include <stdio.h>
#include <string.h>
using namespace std;
int t, n;
int map[64][64];
int dgr[64];
int set[64];
bool ap[64];
int find(int x)
{
    if(set[x] == x)
    {
        return set[x];
    }
    set[x] = find(set[x]);
    return set[x];
}
void dfs(int u)
{
    for(int v = 1; v <= 50; v++)
    {
        while(map[u][v])
        {
            map[u][v]--;
            map[v][u]--;
            dfs(v);
            printf("%d %d\n", v, u);
        }
    }
}
int main()
{
    scanf("%d", &t);
    int _t = t;
    while(t--)
    {
        memset(dgr, 0, sizeof(dgr));
        memset(ap, 0, sizeof(ap));
        memset(map, 0, sizeof(map));
        printf("Case #%d\n", _t - t);
        bool flg = true;
        scanf("%d", &n);
        for(int i = 1; i <= 63; i++)
        {
            set[i] = i;
        }
        for(int i = 1; i <= n; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            map[u][v]++;
            map[v][u]++;
            dgr[u]++;
            dgr[v]++;
            ap[u] = true;
            ap[v] = true;
            if(find(u) != find(v)){ set[find(u)] = find(v); }
        }
        int md = 0;
        for(int i = 1; i <= 50; i++)
        {
            if(ap[i])
            {
                if(md == 0)
                {
                    md = find(i);
                }
                else
                {
                    if(find(i) != md)
                    {
                        flg = false;
                    }
                }
            }
        }
        for(int i = 1; i <= 50; i++)
        {
            flg &= dgr[i] % 2 == 0;
        }
        if(flg)
        {
            for(int i = 1; i <= 50; i++)
            {
                if(ap[i])
                {
                    dfs(i);
                    printf("\n");
                    break;
                }
            }
        }
        else
        {
            printf("some beads may be lost\n\n");
        }
    }
    return 0;
}
