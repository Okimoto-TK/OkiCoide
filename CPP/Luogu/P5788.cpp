#include <stdio.h>
using namespace std;
int ptr;
int s[3000007];
int a[3000007];
int r[3000007];
int n;
int main(int argc, char const *argv[])
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++){
        scanf("%d", &a[i]);
        while(ptr > 0 && a[s[ptr - 1]] < a[i]){
            ptr --;
            r[s[ptr]] = i;
        }
        s[ptr ++] = i;
    }
    for(int i = 1; i <= n; i ++)
        printf("%d ", r[i]);
    return 0;
}