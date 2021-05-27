#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int val[207][207];
long long f[3007][3007][3];
const char rpr[4] = {'A', 'T', 'G', 'C'};
char a[3007];
char b[3007];
int A, B;
int main()
{
    scanf("%s", a + 1);
    int n = strlen(a + 1);
    scanf("%s", b + 1);
    int m = strlen(b + 1);
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            scanf("%d\n", &val[(int)rpr[i]][(int)rpr[j]]);
        }
    }
    scanf("%d %d", &A, &B);
    for (int i = max(n, m); i; --i) {
        f[0][i][0] = f[i][0][0] = f[0][i][2] = f[i][0][1] = -(1LL << 60);
        f[0][i][1] = f[i][0][2] = -A - B * (i - 1);
    }
    f[0][0][1] = f[0][0][2] = -(1LL << 60);
    for(int i = 1; i <= (int)n; i++)
    {
        for(int j = 1; j <= (int)m; j++)
        {
            f[i][j][0]= max(f[i - 1][j - 1][0], max(f[i - 1][j - 1][1], f[i - 1][j - 1][2])) + val[(int)a[i]][(int)b[j]];
            f[i][j][1]= max(f[i][j - 1][1]- B, max(f[i][j - 1][0]- A, f[i][j - 1][2]- A));
            f[i][j][2]= max(f[i - 1][j][2]- B, max(f[i - 1][j][0]- A, f[i - 1][j][1]- A));
        }
    }
    printf("%lld", *max_element(f[n][m], f[n][m] + 2));
    return 0;
}
