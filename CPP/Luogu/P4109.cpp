#include <cstdio>
#include <cmath>
int T;
int run(int l, int r)
{
    int res = 0x7f7f7f7f;
    int ans = 0;
    while(l <= r)
    {
        //printf("%d\n", l);
        int t = l;
        int zero = 0;
        while(t % 10 == 0)
        {
            t /= 10;
            zero++;
        }
        int len = 0;
        int _t = t;
        while(t != 0)
        {
            t /= 10;
            len++;
        }
        int p = len * 2;
        if(_t % 10 == 5) p--;
        if(p < res)
        {
            ans = l;
            res = p;
        }
        l += pow(10, zero);
    }
    return ans;
}
int main()
{
    for(scanf("%d", &T); T != 0; T--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", run(l, r));
    }
    return 0;
}
