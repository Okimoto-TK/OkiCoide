#include <stdio.h>
#include <map>
using namespace std;
int n, m, w, p;
int wt[10007];
int pr[10007];
int tp[10007];
int tw[10007];
int st[10007];
int bp[10007];
map <int, int> to;
int find(int x)
{
    if(st[x] == x){ return st[x]; }
    st[x] = find(st[x]);
    return st[x];
}
inline int getMax(int a, int b){ return a > b ? a : b; }
int main()
{
    for(int i = 0; i <= 10007; i++){ st[i] = i; }
    scanf("%d%d%d", &n, &m, &w);
    for(int i = 1; i <= n; i++){ scanf("%d%d", &wt[i], &pr[i]); }
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        st[find(u)] = find(v);
    }
    for(int i = 1; i <= n; i++)
    {
        if(to[find(i)] == 0){ to[find(i)] = ++p; }
        tp[to[find(i)]] += pr[i];
        tw[to[find(i)]] += wt[i];
    }
    for(int i = 1; i <= p; i++)
    {
        for(int j = w; j >= 1; j--)
        {
            if(j - tw[i] >= 0){ bp[j] = getMax(bp[j], bp[j - tw[i]] + tp[i]); }
        }
    }
    printf("%d", bp[w]);
    return 0;
}
