#include <stdio.h>
#include <string.h>
using namespace std;
char s[1000007];
char x[1000007];
char y[1000007];
int main()
{
    scanf("%s", s);
    bool same = true;
    int len = strlen(s);
    x[len] = '\0';
    y[len] = '\0';
    for(int i = len - 1; i >= 0; i--)
    {
        if(s[i] == 'Z')
        {
            if(same)
            {
                x[i] = '0';
                y[i] = '0';
            }
            else
            {
                printf("-1");
                return 0;
            }
        }
        else if(s[i] == 'X')
        {
            x[i] = '9';
            y[i] = '0';
            same = false;
        }
        else
        {
            x[i] = '0';
            y[i] = '9';
            same = false;
        }
    }
    printf("%s\n", x);
    printf("%s", y);
    return 0;
}
