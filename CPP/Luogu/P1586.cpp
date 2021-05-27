#include <stdio.h>
#include <math.h>
using namespace std;
int f[32770][5];
int t, n;
int main()
{
    for(int j = 1; j <= sqrt(32768); j++)
    {
        for(int i = 1; i <= 32768; i++)
        {
            if(i < j * j)
            {
                continue;
            }
            if(i == j * j)
            {
                f[i][1] += 1;
                continue;
            }
            f[i][2] += f[i - j * j][1];
            f[i][3] += f[i - j * j][2];
            f[i][4] += f[i - j * j][3];
        }
    }
    scanf("%d", &t);
    for(int i = 1; i <= t; i++)
    {
        scanf("%d", &n);
        printf("%d\n", f[n][1] + f[n][2] + f[n][3] + f[n][4]);
    }
    return 0;
}
