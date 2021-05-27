#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
struct node
{
    int chd[4];
    int fail;
    int super;
    int val;
    bool in;
} t[1000007];
int n, m, p;
char s[10000007];
char str[100002][102];
inline int get(char c)
{
    switch(c)
    {
        case 'E': return 0;
        case 'S': return 1;
        case 'W': return 2;
        case 'N': return 3;
        default: return -1;
    }
}
void build()
{
    for(int i = 1; i <= m; i++)
    {
        scanf("%s", str[i]);
        int u = 1;
        int len = strlen(str[i]);
        for(int j = 0; j < len; j++)
        {
            if(t[u].chd[get(str[i][j])] == 0)
            {
                t[u].chd[get(str[i][j])] = ++p;
                t[p].val = get(str[i][j]);
                t[p].super = u;
            }
            u = t[u].chd[get(str[i][j])];
        }
    }
}
void bfs()
{
    std::queue<int> q;
    q.push(1);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int i = 0; i <= 3; i++)
        {
            if(t[u].chd[i] != 0)
            {
                q.push(t[u].chd[i]);
                int v = t[u].fail;
                while(v > 1 && t[v].chd[i] == 0) v = t[v].fail;
                t[t[u].chd[i]].fail = t[v].chd[i];
            }
            else
            {
                t[u].chd[i] = t[t[u].fail].chd[i];
            }
        }
    }
}
void solve()
{
    int u = 1;
    for(int i = 0; i < n; i++)
    {
        int c = get(s[i]);
        int k = t[u].chd[c];
        while(k > 1)
        {
            t[k].in = true;
            //printf("%d", k);
            k = t[k].fail;
        }
        u = t[u].chd[c];
    }
}
int ans[100007];
void getAns()
{
    for(int i = 1; i <= m; i++)
    {
        int u = 1;
        int len = strlen(str[i]);
        for(int j = 0; j < len; j++)
        {
            u = t[u].chd[get(str[i][j])];
            //printf("%d\n", j);
            ans[i] = std::max(ans[i], t[u].in ? j + 1 : -1);
        }
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    scanf("%s", s);
    p = t[0].chd[0] = t[0].chd[1] = t[0].chd[2] = t[0].chd[3] = 1;
    t[1].fail = t[1].super = 0;
    t[0].fail = -1;
    build();
    bfs();
    //check();
    solve();
    getAns();
    for(int i = 1; i <= m; i++)
    {
        printf("%d\n", ans[i]);
    }
    return 0;
}
