#include <stdio.h>
#include <map>
#include <vector>
#include <queue>
using namespace std;
int n, m, p, top, cn, ans;
int to[20007];
int stk[20007];
int low[20007];
int num[20007];
int cnt[20007];
vector <int> vec[20007];
int getMax(int a, int b){ return a > b ? a : b; }
int getMin(int a, int b){ return a < b ? a : b; }
void scc(int u)
{
    stk[top++] = u;
    int g = top;
    low[u] = cn++;
    num[u] = low[u];
    bool f = false;
    for(int i = 0; i < vec[u].size(); i++)
    {
        int v = vec[u][i];
        if(!num[v])
        {
            scc(v);
            low[u] = getMin(low[v], low[u]);
        }
        else if(!to[v]){ low[u] = getMin(low[u], num[v]); }
    }
    if(low[u] == num[u])
    {
        if(top > g){ ans++; }
        for(; top >= g; top--)
        {
            to[stk[top - 1]] = 1;
        }
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    p = n;
    for(int i = 1; i <= n; i++){ vec[0].push_back(i); }
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
    }
    scc(0);
    printf("%d", ans);
    return 0;
}
