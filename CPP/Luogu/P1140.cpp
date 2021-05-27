#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
char a[2007];
char b[2007];
int k;
int f[2007][2007];
int getVal(char x, char y)
{
    if(x == 'A')
    {
        if(y == 'A')
        {
            return 5;
        }
        else if(y == 'C')
        {
            return -1;
        }
        else if(y == 'G')
        {
            return -2;
        }
        else if(y == 'T')
        {
            return -1;
        }
        else
        {
            return -3;
        }
    }
    else if(x == 'C')
    {
        if(y == 'A')
        {
            return -1;
        }
        else if(y == 'C')
        {
            return 5;
        }
        else if(y == 'G')
        {
            return -3;
        }
        else if(y == 'T')
        {
            return -2;
        }
        else
        {
            return -4;
        }
    }
    else if(x == 'G')
    {
        if(y == 'A')
        {
            return -2;
        }
        else if(y == 'C')
        {
            return -3;
        }
        else if(y == 'G')
        {
            return 5;
        }
        else if(y == 'T')
        {
            return -2;
        }
        else
        {
            return -2;
        }
    }
    else if(x == 'T')
    {
        if(y == 'A')
        {
            return -1;
        }
        else if(y == 'C')
        {
            return -2;
        }
        else if(y == 'G')
        {
            return -2;
        }
        else if(y == 'T')
        {
            return 5;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        if(y == 'A')
        {
            return -3;
        }
        else if(y == 'C')
        {
            return -4;
        }
        else if(y == 'G')
        {
            return -2;
        }
        else if(y == 'T')
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
}
int main()
{
    int a_len, b_len;
    scanf("%d%s", &a_len, a);
    scanf("%d%s", &b_len, b);
    for(int i = 1; i <= a_len; i++)
    {
        f[i][0] = f[i - 1][0] + getVal(a[i - 1], '-');
    }
    for(int i = 1; i <= b_len; i++)
    {
        f[0][i] = f[0][i - 1] + getVal('-', b[i - 1]);
    }
    for(int i = 1; i <= a_len; i++)
    {
        int ap = i - 1;
        for(int j = 1; j <= b_len; j++)
        {
            int bp = j - 1;
            f[i][j] = max(f[i - 1][j] + getVal(a[ap], '-'), max(f[i][j - 1] + getVal('-', b[bp]), f[i - 1][j - 1] + getVal(a[ap], b[bp])));
        }
    }
    printf("%d", f[a_len][b_len]);
    return 0;
}
