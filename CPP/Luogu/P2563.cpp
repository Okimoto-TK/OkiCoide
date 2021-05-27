#include <stdio.h>
#include <string.h>
#include <algorithm>
bool isP(int x)
{
    for(int i = 2; i < x; i++)
    {
        if(x % i == 0)
        {
            return false;
        }
    }
    return true;
}
int n;
int f[1007];
int main()
{
    while(scanf("%d", &n) != EOF)
    {
        memset(f, 0, sizeof(f));
        f[0] = 1;
        for(int x = 2; x <= n; x++)
        {
            if(isP(x))
            {
                for(int i = x; i <= 200; i++)
                {
                    f[i] += f[i - x];
                }
            }
        }
        printf("%d\n", f[n]);
    }
    return 0;
}
