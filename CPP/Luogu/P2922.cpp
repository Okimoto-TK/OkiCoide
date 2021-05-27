#include <stdio.h>
using namespace std;
int m, n, p = 1;
struct node
{
    int val;
    int pass;
    int end;
    int chd[2];
    node()
    {
        val = -1;
        pass = end = 0;
        chd[0] = chd[1] = -1;
    }
} trie[500007];
int main()
{
    scanf("%d%d", &m, &n);
    for(int i = 1; i <= m; i++)
    {
        int b;
        scanf("%d", &b);
        int u = 1, v;
        for(int j = 1; j <= b; j++)
        {
            scanf("%d", &v);
            if(trie[u].chd[v] == -1)
            {
                trie[u].chd[v] = ++p;
                trie[p].val = v;
            }
            u = trie[u].chd[v];
            trie[u].pass++;
        }
        trie[u].end++;
    }
    for(int i = 1; i <= n; i++)
    {
        int ans = 0;
        int c;
        scanf("%d", &c);
        int u = 1, v;
        bool fail = false;
        for(int j = 1; j <= c; j++)
        {
            scanf("%d", &v);
            if(fail)
            {
                continue;
            }
            if(trie[u].chd[v] == -1)
            {
                printf("%d\n", ans);
                fail = true;
                continue;
            }
            u = trie[u].chd[v];
            ans += trie[u].end;
        }
        ans += trie[u].pass - trie[u].end;
        if(!fail)
        {
            printf("%d\n", ans);
        }
    }
    return 0;
}
