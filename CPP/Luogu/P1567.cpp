#include <stdio.h>
#include <algorithm>
using namespace std;
int n;
int a[1000007];
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    int s = 0;
    int t = 0;
    int l = -1;
    for(int i = 1; i <= n; i++)
    {
        if(a[i] > l)
        {
            t += 1;
        }
        else
        {
            t = 1;
        }
        l = a[i];
        s = max(s, t);
    }
    printf("%d", s);
    return 0;
}
