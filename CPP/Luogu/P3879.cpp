#include <stdio.h>
#include <string>
#include <map>
#include <set>
using namespace std;
int n, m, p;
char buf[32];
map<string, int> myHash;
set<int> s[50007];
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        int l;
        scanf("%d", &l);
        for(int j = 1; j <= l; j++)
        {
            scanf("%s", buf);
            string str = buf;
            if(myHash[str] == 0)
            {
                myHash[str] = ++p;
            }
            int op = myHash[str];
            s[op].insert(s[op].end(), i);
        }
    }
    scanf("%d", &m);
    for(int i = 1; i <= m; i++)
    {
        scanf("%s", buf);
        string str = buf;
        if(myHash[str] == 0)
        {
            printf("\n");
            continue;
        }
        int op = myHash[str];
        for(set<int>::iterator it = s[op].begin(); it != s[op].end();)
        {
            printf("%d", *it);
            if(++it != s[op].end())
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
