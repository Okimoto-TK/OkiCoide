#include <stdio.h>
#include <algorithm>
using namespace std;
int n;
int p[1007];
int f[1007];
int main()
{
    scanf("%d", &n);
    for(int i = 2; i <= n; i++)
    {
        for(int j = 1; j < i; j++)
        {
            if(i % j == 0)
            {
                p[i] += j;
            }
        }
    }
    for(int i = 2; i <= n; i++)
    {
        for(int j = n; j >= i; j--)
        {
            f[j] = max(f[j], f[j - i] + p[i]);
        }
    }
    printf("%d", f[n]);
    return 0;
}
