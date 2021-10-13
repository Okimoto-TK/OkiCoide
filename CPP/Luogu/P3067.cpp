#include <cstdio>
#include <vector>
#include <unordered_map>
int n;
int m[25];
bool vis[1 << 21];
std::unordered_map<int, std::vector<int> > map;
void Dfs1(int cur, int sta, int sum)
{
    if(cur == n / 2 + 1)
    {
        map[sum].push_back(sta);
        return;
    }
    Dfs1(cur + 1, sta | (1 << (cur - 1)), sum + m[cur]);
    Dfs1(cur + 1, sta | (1 << (cur - 1)), sum - m[cur]);
    Dfs1(cur + 1, sta, sum);
}
void Dfs2(int cur, int sta, int sum)
{
    if(cur == n + 1)
    {
        for(auto x : map[sum])
        {
            vis[x | sta] = true;
        }
        return;
    }
    Dfs2(cur + 1, sta | (1 << (cur - 1)), sum + m[cur]);
    Dfs2(cur + 1, sta | (1 << (cur - 1)), sum - m[cur]);
    Dfs2(cur + 1, sta, sum);
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &m[i]);
    Dfs1(1, 0, 0);
    Dfs2(n / 2 + 1, 0, 0);
    int ans = 0;
    for(int i = 1; i <= 1 << n; i++) ans += vis[i] ? 1 : 0;
    printf("%d", ans);
    return 0;
}
