#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#define N 200007
using namespace std;
struct edge
{
    int v;
    bool w;
    edge(int x, bool y)
    {
        v = x;
        w = y;
    }
};
vector<edge> E[N];
int n;
int dfs1(int u, int f)
{
    int len = E[u].size();
    int res = 0;
    for(int i = 0; i < len; i++)
    {
        int v = E[u][i].v;
        bool w = E[u][i].w;
        if(v == f)
        {
            continue;
        }
        res += dfs1(v, u) + (w ? 1 : 0);
    }
    return res;
}
int lss;
int buf;
priority_queue<int, vector<int>, greater<int> > ans;
void dfs2(int u, int f, bool w)
{
    buf += w ? -1 : 1;
    if(buf < lss)
    {
        lss = buf;
        while(!ans.empty())
        {
            ans.pop();
        }
        ans.push(u);
    }
    else if(buf == lss)
    {
        ans.push(u);
    }
    int len = E[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = E[u][i].v;
        bool w = E[u][i].w;
        if(v == f)
        {
            continue;
        }
        dfs2(v, u, w);
    }
    buf -= w ? -1 : 1;
}
int main()
{
    while(scanf("%d", &n) != EOF)
    {
        for(int i = 1; i <= n; i++)
        {
            E[i].clear();
        }
        while(!ans.empty())
        {
            ans.pop();
        }
        for(int i = 1; i < n; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            E[u].push_back(edge(v, false));
            E[v].push_back(edge(u, true));
        }
        lss = buf = dfs1(1, 0);
        ans.push(1);
        int len = E[1].size();
        for(int i = 0; i < len; i++)
        {
            int v = E[1][i].v;
            bool w = E[1][i].w;
            dfs2(v, 1, w);
        }
        printf("%d\n", lss);
        while(!ans.empty())
        {
            printf("%d ", ans.top());
            ans.pop();
        }
        printf("\n");
    }
    return 0;
}
