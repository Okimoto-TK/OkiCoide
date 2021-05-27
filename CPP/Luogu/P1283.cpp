#include <cstdio>
#include <algorithm>
#include <vector>
#define N 20
int n;
struct Sqr
{
    int x1, y1, x2, y2, c;
    std::pair<int, int> uL() { return std::make_pair(x1, y1); }
    std::pair<int, int> uR() { return std::make_pair(x2, y1); }
    std::pair<int, int> dL() { return std::make_pair(x1, y2); }
    std::pair<int, int> dR() { return std::make_pair(x2, y2); }
    void init() { scanf("%d%d%d%d%d", &y1, &x1, &y2, &x2, &c); }
} sqr[N];
std::vector<int> g[N];
int ans = 0x3f3f3f3f;
bool vis[N];
bool check(int i)
{
    int len = g[i].size();
    for(int j = 0; j < len; j++)
    {
        if(!vis[g[i][j]]){ return false; }
    }
    return true;
}
void dfs(int cost, int step, int color)
{
    if(cost >= ans) { return; }
    if(step == n)
    {
        ans = cost;
        return;
    }
    for(int i = 1; i <= n; i++)
    {
        if(vis[i] || !check(i)){ continue; }
        vis[i] = true;
        dfs(cost + (color == sqr[i].c ? 0 : 1), step + 1, sqr[i].c);
        vis[i] = false;
    }
}
bool cmp(int i, int j) { return sqr[j].y2 == sqr[i].y1 && ((sqr[j].x1 >= sqr[i].x1 && sqr[j].x1 < sqr[i].x2) || (sqr[j].x2 > sqr[i].x1 && sqr[j].x2 <= sqr[i].x2)); }
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) sqr[i].init();
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(i == j) { continue; }
            if(cmp(i, j)) { g[i].push_back(j); }
        }
    }
    dfs(0, 0, 0);
    printf("%d", ans);
    return 0;
}
