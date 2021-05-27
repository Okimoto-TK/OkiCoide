#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
struct node
{
    bool isU;
    int val;
    node()
    {
        isU = false;
        val = 0;
    }
};
int getFac(int x, int f)
{
    int r = 0;
    while(x % f == 0 && x)
    {
        x /= f;
        r++;
    }
    return r;
}
int n;
int a[1007][1007];
int b[1007][1007];
bool c[1007][1007];
node f[1007][1007][2];
void getRoad(int i, int j, int k)
{
    if(i == 1 && j == 1)
    {
        return;
    }
    if(f[i][j][k].isU)
    {
        getRoad(i - 1, j, k);
        printf("D");
    }
    else
    {
        getRoad(i, j - 1, k);
        printf("R");
    }
}
bool zero = false;
int x, y;
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            scanf("%d", &a[i][j]);
            if(a[i][j] == 0)
            {
                zero = true;
                x = i;
                y = j;
                c[i][j] = true;
            }
            b[i][j] = getFac(a[i][j], 5);
            a[i][j] = getFac(a[i][j], 2);
        }
    }
    f[1][1][0].val = a[1][1];
    f[1][1][0].isU = false;
    f[1][1][1].val = b[1][1];
    f[1][1][1].isU = false;
    for(int len = 3; len <= n + n; len++)
    {
        for(int i = max(1, len - n); i <= n && len - i >= 1; i++)
        {
            int j = len - i;
            if(c[i][j])
            {
                f[i][j][0].val = 20000000;
                f[i][j][1].val = 20000000;
                continue;
            }
            if(i != 1 && j != 1 && !c[i - 1][j] && !c[i][j - 1])
            {
                if(f[i - 1][j][0].val < f[i][j - 1][0].val)
                {
                    f[i][j][0].val = f[i - 1][j][0].val + a[i][j];
                    f[i][j][0].isU = true;
                }
                else
                {
                    f[i][j][0].val = f[i][j - 1][0].val + a[i][j];
                    f[i][j][0].isU = false;
                }
                if(f[i - 1][j][1].val < f[i][j - 1][1].val)
                {
                    f[i][j][1].val = f[i - 1][j][1].val + b[i][j];
                    f[i][j][1].isU = true;
                }
                else
                {
                    f[i][j][1].val = f[i][j - 1][1].val + b[i][j];
                    f[i][j][1].isU = false;
                }
            }
            else if(i != 1 && !c[i - 1][j])
            {
                f[i][j][0].val = f[i - 1][j][0].val + a[i][j];
                f[i][j][0].isU = true;
                f[i][j][1].val = f[i - 1][j][1].val + b[i][j];
                f[i][j][1].isU = true;
            }
            else if(j != 1 && !c[i][j - 1])
            {
                f[i][j][0].val = f[i][j - 1][0].val + a[i][j];
                f[i][j][0].isU = false;
                f[i][j][1].val = f[i][j - 1][1].val + b[i][j];
                f[i][j][1].isU = false;
            }
            else
            {
                f[i][j][0].val = 20000000;
                f[i][j][1].val = 20000000;
            }
        }
    }
    int ans = min(f[n][n][0].val, f[n][n][1].val);
    if(zero && ans > 1)
    {
        printf("1\n");
        for(int i = 1; i <= x - 1; i++)
        {
            printf("D");
        }
        for(int i = 1; i <= y - 1; i++)
        {
            printf("R");
        }
        for(int i = 1; i <= n - x; i++)
        {
            printf("D");
        }
        for(int i = 1; i <= n - y; i++)
        {
            printf("R");
        }
        return 0;
    }
    printf("%d\n", min(f[n][n][0].val, f[n][n][1].val));
    getRoad(n, n, f[n][n][0].val < f[n][n][1].val ? 0 : 1);
    return 0;
}
