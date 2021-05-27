#include <stdio.h>
using namespace std;
int n, k;
const int p = 10000;
int f[1007][5007];
int main()
{
    scanf("%d%d", &n, &k);
    f[1][0] = 1;
    for(int i = 2; i <= n; i++)
    {
        int sum = 0;
        for(int j = 0; j <= k; j++)
        {
            (sum += f[i - 1][j]) %= p;
            f[i][j] = sum;
            if(j - i + 1 >= 0)
            {
                (((sum -= f[i - 1][j - i + 1]) %= p) += p) %= p;
            }
        }
    }
    printf("%d", f[n][k]);
    return 0;
}
