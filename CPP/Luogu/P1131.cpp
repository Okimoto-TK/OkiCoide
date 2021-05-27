#include <stdio.h>
#include <vector>
#include <algorithm>
#define N 500007
using namespace std;
int n, s;
long long ans;
struct edge
{
    int v;
    int w;
    edge(int x, int y)
    {
        v = x;
        w = y;
    }
};
vector<edge> E[N];
long long dfs(int u, int f)
{
    int len = E[u].size();
    long long sum = 0;
    long long syn = 0;
    for(int i = 0; i < len; i++)
    {
        int v = E[u][i].v;
        if(f == v)
        {
            continue;
        }
        long long w = E[u][i].w;
        w += dfs(v, u);
        syn = max(w, syn);
        sum += w;
    }
    ans += syn * (len - (u != s)) - sum;
    return syn;
}
int main()
{
    scanf("%d", &n);
    scanf("%d", &s);
    for(int i = 1; i < n; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        E[u].push_back(edge(v, w));
        E[v].push_back(edge(u, w));
    }
    dfs(s, 0);
    printf("%lld", ans);
    return 0;
}
