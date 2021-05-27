#include <stdio.h>
using namespace std;
int n;
int deg[128];
int set[128];
int map[128][128];
int ans[10007];
int top;
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
    for(int v = 0; v < 128; v++)
    {
        while(map[u][v])
        {
            map[u][v]--;
            if(v != u){ map[v][u]--; }
            dfs(v);
            ans[top++] = v - 1 + 'A';
        }
    }
}
int main()
{
    for(int i = 1; i < 127; i++)
    {
        set[i] = i;
    }
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        char buf[3];
        scanf("%s", buf);
        int a = buf[0] - 'A' + 1;
        int b = buf[1] - 'A' + 1;
        map[a][b] = 1;
        map[b][a] = 1;
        deg[a]++;
        deg[b]++;
        if(find(a) != find(b)){ set[find(a)] = find(b); }
    }
    bool hv = true;
    bool rd = false;
    int md = 0;
    int cnt = 0;
    for(int i = 1; i < 128; i++)
    {
        rd |= (deg[i] % 2);
        cnt += (deg[i] % 2);
        if(deg[i])
        {
            if(md == 0)
            {
                md = find(i);
            }
            else
            {
                hv &= (md == find(i));
            }
        }
    }
    if(!hv || (cnt != 0 && cnt != 2))
    {
        printf("No Solution");
        return 0;
    }
    if(rd)
    {
        for(int i = 0; i < 128; i++)
        {
            if(deg[i] % 2)
            {
                dfs(i);
                ans[top++] = i - 1 + 'A';
                break;
            }
        }
    }
    else
    {
        for(int i = 1; i < 128; i++)
        {
            if(deg[i])
            {
                dfs(i);
                ans[top++] = i - 1 + 'A';
                break;
            }
        }
    }
    for(top = top - 1; top >= 0; top--)
    {
        printf("%c", ans[top]);
    }
    return 0;
}
