#include <stdio.h>
using namespace std;
int getMax(int a , int b)
{
    return a > b ? a : b;
}
void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}
int main()
{
    int i, j;
    while(scanf("%d%d", &i, &j) != EOF)
    {
        printf("%d %d ", i, j);
        if(i > j){ swap(i, j); }
        int ans = 0;
        for(; i <= j; ++i)
        {
            int x = i;
            int c = 1;
            while(x != 1)
            {
                if(x % 2 == 1){ x = 3 * x + 1; }
                else{ x = x / 2; }
                c++;
            }
            ans = getMax(ans, c);
        }
        printf("%d\n", ans);
    }
    return 0;
}
