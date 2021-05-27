#include <stdio.h>
using namespace std;
int n, m;
int main()
{
    scanf("%d", &m);
    int a = 0;
    int b = 1;
    for(int i = 2; true; i++)
    {
        int v = (a + b) % m;
        if(b % m == 0 && v == 1)
        {
            printf("%d", i - 1);
            return 0;
        }
        a = b;
        b = v;
    }
    return 0;
}
