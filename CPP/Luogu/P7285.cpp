#include <stdio.h>
#include <string.h>
using namespace std;
int arr[100007];
int main()
{
    int t;
    scanf("%d", &t);
    for(int i = 1; i <= t; i++)
    {
        int n, a = 0;
        scanf("%d", &n);
        for(int i = 0; i < n; i ++)
        {
            scanf("%d", &arr[i]);
        }
        int last = 1;
        for(int j = 0; j < n; j++)
        {
            int c = arr[j];
            if(last = 1 && arr[j] == 0)
            {
                a++;
            }
            last = arr[j];
        }
        printf("%d\n", n - a);
        for(int j = 0; j < n; j++)
        {
            printf("%d ", 1);
        }
        printf("\n");
    }
    return 0;
}
