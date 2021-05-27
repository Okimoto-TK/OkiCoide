#include <stdio.h>
#include <algorithm>
#include <bitset>
using namespace std;
int n, m, ans;
int a[30];
int bit(int x)
{
    int r = 0;
    while(x)
    {
        x &= (x - 1);
        r++;
    }
    return r;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    for(int i = 0; i < 1 << (n + 1); i++)
    {
        if(bit(i) == n - m)
        {
            bitset <2007> b;
            b[0] = true;
            for(int j = 0; j < n; j++)
            {
                if(i & (1 << j))
                {
                    b = b | b << a[j];
                }
            }
            ans = max(ans, (int)b.count());
        }
    }
    printf("%d", ans - 1);
    return 0;
}
