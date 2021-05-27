#include <stdio.h>
#include <string.h>
using namespace std;
int q, pool = 1;
int digit[32];
struct node
{
    int chd[2];
    int cnt;
    node()
    {
        cnt = chd[0] = chd[1] = 0;
    }
} trie[10000007];
int main()
{
    scanf("%d", &q);
    int _u = 1;
    for(int i = 30; i >= 0; i--)
    {
        if(trie[_u].chd[0] == 0)
        {
            trie[_u].chd[0] = ++pool;
        }
        _u = trie[_u].chd[0];
        trie[_u].cnt++;
    }
    while(q--)
    {
        memset(digit, 0, sizeof(digit));
        char opt[2];
        int x, cnt = 0;
        scanf("%s%d", opt, &x);
        while(x)
        {
            digit[cnt++] = x % 2;
            x >>= 1;
        }
        if(opt[0] == '+')
        {
            int u = 1;
            for(int i = 30; i >= 0; i--)
            {
                int v = digit[i];
                if(trie[u].chd[v] == 0)
                {
                    trie[u].chd[v] = ++pool;
                }
                u = trie[u].chd[v];
                trie[u].cnt++;
            }
        }
        else if(opt[0] == '-')
        {
            int u = 1;
            for(int i = 30; i >= 0; i--)
            {
                int v = digit[i];
                u = trie[u].chd[v];
                trie[u].cnt--;
            }
        }
        else
        {
            int u = 1;
            int ans = 0;
            for(int i = 30; i >= 0; i--)
            {
                int v = digit[i] ^ 1;
                if(trie[u].chd[v] == 0 || trie[trie[u].chd[v]].cnt == 0)
                {
                    u = trie[u].chd[v ^ 1];
                }
                else
                {
                    u = trie[u].chd[v];
                    ans += 1 << i;
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
