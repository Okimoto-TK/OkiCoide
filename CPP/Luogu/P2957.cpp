#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
char s[128];
char t[128];
int ans;
int _ans;
int main()
{
    scanf("%s", s);
    scanf("%s", t);
    int len = min(strlen(s), strlen(t));
    for(int i = 0; i <= len; i++)
    {
        int se = i;
        int ts = strlen(t) - i;
        int te = strlen(t);
        bool f = true;
        for(int si = 0, ti = ts; si < se && ti < te; si++, ti++)
        {
            if(s[si] != t[ti])
            {
                f = false;
                break;
            }
        }
        if(f){ ans = i; }
    }
    char tmp[128];
    strcpy(tmp, s);
    strcpy(s, t);
    strcpy(t, tmp);
    len = min(strlen(s), strlen(t));
    for(int i = 0; i <= len; i++)
    {
        int se = i;
        int ts = strlen(t) - i;
        int te = strlen(t);
        bool f = true;
        for(int si = 0, ti = ts; si < se && ti < te; si++, ti++)
        {
            if(s[si] != t[ti])
            {
                f = false;
                break;
            }
        }
        if(f){ _ans = i; }
    }
    printf("%d", max(ans, _ans));
}
