#include <stdio.h>
#include <vector>
#include <queue>
#define N 1000007
using namespace std;
int n, s, sum;
int t[N];
vector<int> E[N];
queue<int> ans;
int f[N];
void dfs(int u)
{
    int res = t[u];
    int len = E[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = E[u][i];
        dfs(v);
        res += f[v];
    }
    if(res == sum && u != s)
    {
        res = 0;
        ans.push(u);
    }
    f[u] = res;
}
int main()
{
    scanf("%d", &n);
    for(int v = 1; v <= n; v++)
    {
        int u;
        scanf("%d%d", &u, &t[v]);
        sum += t[v];
        if(u == 0)
        {
            s = v;
        }
        else
        {
            E[u].push_back(v);
        }
    }
    if(sum % 3 != 0)
    {
        printf("-1");
        return 0;
    }
    sum /= 3;
    dfs(s);
    if(ans.size() >= 2)
    {
        int a = ans.front();
        ans.pop();
        int b = ans.front();
        printf("%d %d", a, b);
    }
    else
    {
        printf("-1");
    }
    return 0;
}
