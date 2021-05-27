#include <stdio.h>
using namespace std;
int n, m;
int a[15007];
int b[40007];
int f[15007][4];
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        scanf("%d", &b[i]);
        a[b[i]]++;
    }
    for(int k = 1; 9 * k < n; k++)
    {
        int sum = 0;
        for(int D = 9 * k + 2; D <= n; D++)
        {
            int C = D - k;
            int B = D - 7 * k - 1;
            int A = D - 9 * k - 1;
            sum += a[A] * a[B];
            f[C][2] += sum * a[D];
            f[D][3] += sum * a[C];
        }
        sum = 0;
        for(int A = n - 9 * k - 1; A >= 1; A--)
        {
            int B = A + 2 * k;
            int C = A + 8 * k + 1;
            int D = A + 9 * k + 1;
            sum += a[C] * a[D];
            f[A][0] += sum * a[B];
            f[B][1] += sum * a[A];
        }
    }
    for(int i = 1; i <= m; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            printf("%d ", f[b[i]][j]);
        }
        printf("\n");
    }
    return 0;
}
