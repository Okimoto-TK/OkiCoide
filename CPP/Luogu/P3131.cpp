#include <stdio.h>
#include <algorithm>
using namespace std;
int n;
int pre[50007];
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        pre[i] = (pre[i - 1] + x % 7) % 7;
    }
    int len = 0;
    for(int i = 1; i <= n - len; i++)
    {
        for(int j = i + len; j <= n; j++)
        {
            if((pre[j] - pre[i - 1]) % 7 == 0)
            {
                len = j - i + 1;
            }
        }
    }
    printf("%d", len);
    return 0;
}
