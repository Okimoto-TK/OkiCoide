#include <stdio.h>
using namespace std;
struct node
{
    int val;
    int cnt;
    int chd[2];
    node()
    {
        val = 0;
        chd[0] = -1;
        chd[1] = -1;
        cnt = 0;
    }
} trie[2700007];
int digit[30];
int _digit[30];
int q, cnt, _cnt, pool = 1;
int main()
{
    scanf("%d", &q);
    while(q--)
    {
        int opt;
        scanf("%d", &opt);
        if(opt == 1)
        {
            cnt = 0;
            for(int i = 0; i < 30; i++)
            {
                digit[i] = 0;
            }
            int p;
            scanf("%d", &p);
            while(p)
            {
                digit[cnt++] = p % 2;
                p /= 2;
            }
            int u = 1;
            for(int i = 27; i >= 0; i--)
            {
                int v = digit[i];
                if(trie[u].chd[v] == -1)
                {
                    trie[u].chd[v] = ++pool;
                    trie[p].val = v;
                }
                u = trie[u].chd[v];
                trie[u].cnt++;
            }
        }
        else if(opt == 2)
        {
            cnt = 0;
            for(int i = 0; i < 30; i++)
            {
                digit[i] = 0;
            }
            int p;
            scanf("%d", &p);
            while(p)
            {
                digit[cnt++] = p % 2;
                p /= 2;
            }
            int u = 1;
            for(int i = 27; i >= 0; i--)
            {
                int v = digit[i];
                u = trie[u].chd[v];
                trie[u].cnt--;
            }
        }
        else
        {
            cnt = 0;
            _cnt = 0;
            for(int i = 0; i < 30; i++)
            {
                digit[i] = 0;
                _digit[i] = 0;
            }
            int p, l;
            scanf("%d%d", &p, &l);
            while(p)
            {
                digit[cnt++] = p % 2;
                p /= 2;
            }
            while(l)
            {
                _digit[_cnt++] = l % 2;
                l /= 2;
            }
            int u = 1;
            int ans = 0;
            for(int i = 27; i >= 0; i--)
            {
                int v = digit[i];
                int _v = _digit[i];
                if(_v)
                {
                    if(trie[u].chd[v] != -1)
                    {
                        ans += trie[trie[u].chd[v]].cnt;
                    }
                    if(trie[u].chd[v ^ 1] != -1)
                    {
                        u = trie[u].chd[v ^ 1];
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    if(trie[u].chd[v] != -1)
                    {
                        u = trie[u].chd[v];
                    }
                    else
                    {
                        break;
                    }
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
