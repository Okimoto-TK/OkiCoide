#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int n, c;
int lmp[64][2];
int sum[64];
int f[64][64][2];
int main()
{
    memset(f, 0x3f, sizeof(f));
    scanf("%d%d", &n, &c);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d%d", &lmp[i][0], &lmp[i][1]);
        sum[i] = sum[i - 1] + lmp[i][1];
    }
    f[c][c][1] = 0;
    f[c][c][0] = 0;
    for(int k = 1; k < n; k++)
    {
        for(int i = max(1, c - k); i <= min(n - k, c); i++)
        {
            int j = i + k;
            int x = f[i + 1][j][0] + (lmp[i + 1][0] - lmp[i][0]) * (sum[n] - (sum[j] - sum[i]));
            int y = f[i + 1][j][1] + (lmp[j][0] - lmp[i][0]) * (sum[n] - (sum[j] - sum[i]));
            f[i][j][0] = min(x, y);
            x = f[i][j - 1][1] + (lmp[j][0] - lmp[j - 1][0]) * (sum[n] - (sum[j - 1] - sum[i - 1]));
            y = f[i][j - 1][0] + (lmp[j][0] - lmp[i][0]) * (sum[n] - sum[j - 1] + sum[i - 1]);
            f[i][j][1] = min(x, y);
        }
    }
    printf("%d", min(f[1][n][0], f[1][n][1]));
}
