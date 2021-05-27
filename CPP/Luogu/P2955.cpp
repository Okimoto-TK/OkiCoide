#include <stdio.h>
#include <string.h>
using namespace std;
int n;
int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        char s[64];
        scanf("%s", s);
        int a = s[strlen(s) - 1];
        if(a & 1)
        {
            printf("odd\n");
        }
        else
        {
            printf("even\n");
        }
    }
    return 0;
}
