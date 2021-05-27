#include <stdio.h>
using namespace std;
int n;
int main()
{
    scanf("%d", &n);
    printf("%d\n", n);
    for(int i = 1; i <= n; i++)
    {
        if(i & 1)
        {
            for(int j = 1; j <= i; j++)
            {
                printf("0");
            }
            for(int j = i + 1; j <= n; j++)
            {
                printf("1");
            }
        }
        else
        {
            for(int j = 1; j <= i; j++)
            {
                printf("1");
            }
            for(int j = i + 1; j <= n; j++)
            {
                printf("0");
            }
        }
        printf("\n");
    }
    return 0;
}
