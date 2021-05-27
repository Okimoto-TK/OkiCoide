#include <stdio.h>
using namespace std;
int l, n;
int a[100007];
int ans1, ans2;
int main()
{
    scanf("%d%d", &l, &n);
    for(int i = 1; i <= n; i++)
    {
        int opt;
        scanf("%d", &opt);
        if(opt == 0)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            for(int j = x; j <= y; j++)
            {
                if(a[j] == 2)
                {
                    ans2++;
                }
                a[j] = 1;
            }
        }
        else
        {
            int x, y;
            scanf("%d%d", &x, &y);
            for(int j = x; j <= y; j++)
            {
                if(a[j] == 1)
                {
                    a[j] = 2;
                }
            }
        }
    }
    for(int i = 0; i <= l; i++)
    {
        if(a[i] == 2)
        {
            ans1++;
        }
    }
    printf("%d\n%d", ans1, ans2);
    return 0;
}
