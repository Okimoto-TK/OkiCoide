#include <stdio.h>
#include <algorithm>
using namespace std;
int n;
int s[30007];
int t[30007];
int p[30007];
void init()
{
    for(int i = 1; i <= 30000; i++)
    {
        s[i] = i;
        t[i] = 1;
    }
}
int find(int x)
{
    if(s[x] == x)
    {
        return x;
    }
    int f = s[x];
    s[x] = find(s[x]);
    p[x] += p[f];
    return s[x];
}
void merge(int i, int j)
{
    int si = find(i);
    int sj = find(j);
    s[si] = sj;
    p[si] = t[sj];
    t[sj] += t[si];
}
int main()
{
    init();
    scanf("%d", &n);
    while(n--)
    {
        char opt[2];
        int i, j;
        scanf("%s%d%d", opt, &i, &j);
        if(opt[0] == 'M')
        {
            merge(i, j);
        }
        else
        {
            if(find(i) != find(j))
            {
                printf("-1\n");
                continue;
            }
            int ans = max(abs(p[i] - p[j]) - 1, 0);
            printf("%d\n", ans);
        }
    }
    return 0;
}
