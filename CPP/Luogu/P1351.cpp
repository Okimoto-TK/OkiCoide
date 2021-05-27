#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
struct node
{
    int spr;
    int w;
    int max;
    long long sum;
    node()
    {
        spr = 0;
        w = 0;
        sum = 0;
        max = 0;
    }
};
int n;
int ans;
long long sum;
const int p = 10007;
vector <int> vec[200007];
node tree[200007];
void dfs(int s, int u)
{
    int len = vec[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = vec[u][i];
        if(v == s)
        {
            tree[u].spr = v;
            continue;
        }
        (sum += tree[v].w * tree[u].sum % p) %= p;
        ans = max(ans, tree[u].max * tree[v].w);
        (tree[u].sum += tree[v].w) %= p;
        tree[u].max = max(tree[u].max, tree[v].w);
        dfs(u, v);
    }
    if(tree[tree[u].spr].spr != 0)
    {
        (sum += tree[u].w * tree[tree[tree[u].spr].spr].w) %= p;
        ans = max(ans, tree[u].w * tree[tree[tree[u].spr].spr].w);
    }
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &tree[i].w);
    }
    dfs(0, 1);
    printf("%d %lld", ans, sum * 2 % p);
    return 0;
}
