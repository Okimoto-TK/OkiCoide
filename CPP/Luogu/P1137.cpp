#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
int n, m;
int in_dgr[100007];
int f[100007];
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
            in_dgr[v]--;
            f[v] = max(f[v], f[u] + 1);
            if(in_dgr[v] == 0)
            {
                q.push(v);
            }
        }
    }
    for(int i = 1; i <= n; i++)
    {
        printf("%d\n", f[i]);
    }
    return 0;
}
