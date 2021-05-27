#include <stdio.h>
using namespace std;
int a[10007];
int n;
int main(int argc, char const *argv[])
{
    scanf("%d", &n);
    for(int i = 2; i <= n; i ++){
        int x = i;
        for(int j = 2; j <= x && x != 1; j ++){
            while(x % j == 0){
                x /= j;
                a[j] ++;
            }
        }
        if(x > 1)
            a[x] ++;
    }
    for(int i = 2; i <= n; i ++)
        if(a[i])
            printf("%d %d\n", i, a[i]);
    return 0;
}