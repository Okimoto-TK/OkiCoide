#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
char a[2007];
char b[2007];
int k;
int f[2007][2007];
int getVal(int ap, int bp)
{
    if(a[ap] == ' ' && b[bp] == ' ')
    {
        return 0;
    }
    else if(a[ap] == ' ' || b[bp] == ' ')
    {
        return k;
    }
    else
    {
        return abs((int)(a[ap] - b[bp]));
    }
}
int main()
{
    scanf("%s", a);
    int a_len = strlen(a);
    scanf("%s", b);
    int b_len = strlen(b);
    scanf("%d", &k);
    for(int i = 1; i <= max(a_len, b_len); i++)
    {
        f[0][i] = i * k;
        f[i][0] = i * k;
    }
    for(int i = 1; i <= a_len; i++)
    {
        int ap = i - 1;
        for(int j = 1; j <= b_len; j++)
        {
            int bp = j - 1;
            f[i][j] = min(f[i - 1][j] + k, min(f[i][j - 1] + k, f[i - 1][j - 1] + getVal(ap, bp)));
        }
    }
    printf("%d", f[a_len][b_len]);
    return 0;
}
