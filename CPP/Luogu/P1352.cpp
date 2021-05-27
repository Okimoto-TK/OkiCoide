#include <stdio.h>
#include <vector>
using namespace std;
struct node
{
    vector <int> ch;
    short vl;
};
int n;
node t[10007];
int f[10007];
bool r[10007];
bool b[10007];
int ans;
int dfs(int u)
{
    int ans1 = t[u].vl;
    for(int i = 0; i < (t[u].ch).size(); ++i)
    {
        int v = t[u].ch[i];
        for(int j = 0; j < (t[v].ch).size(); ++j)
        {
            int to = t[v].ch[j];
            ans1 += r[to] ? f[to] : dfs(to);
        }
    }
    int ans2 = 0;
    for(int i = 0; i < (t[u].ch).size(); ++i)
    {
        int v = t[u].ch[i];
        ans2 += r[u] ? f[u] : dfs(v);
    }
    r[u] = true;
    f[u] = ans1 > ans2 ? ans1 : ans2;
    return f[u];
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){ scanf("%d", &t[i].vl); }
    for(int i = 1; i < n; i++)
    {
        int l, k;
        scanf("%d%d", &l, &k);
        (t[k].ch).push_back(l);
        b[l] = true;
    }
    for(int i = 1; i <= n; ++i)
    {
        if(!b[i]){ ans += dfs(i); }
    }
    printf("%d", ans);
    return 0;
}
