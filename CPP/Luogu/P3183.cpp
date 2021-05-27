#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int n, m;
int f[100007];
int rec_dgr[100007];
int in_dgr[100007];
int out_dgr[100007];
vector <int> vec[100007];
queue <int> q;
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        in_dgr[v]++;
        rec_dgr[v]++;
        out_dgr[u]++;
    }
    for(int i = 1; i <= n; i++)
    {
        if(in_dgr[i] == 0)
        {
            f[i] = 1;
            q.push(i);
        }
    }
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        int len = vec[u].size();
        for(int i = 0; i < len; i++)
        {
            int v = vec[u][i];
            f[v] += f[u];
            in_dgr[v] -= 1;
            if(in_dgr[v] == 0)
            {
                q.push(v);
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        if(out_dgr[i] == 0 && rec_dgr[i] != 0)
        {
            ans += f[i];
        }
    }
    printf("%d", ans);
    return 0;
}
