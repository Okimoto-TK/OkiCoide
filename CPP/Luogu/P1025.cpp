#include <stdio.h>
using namespace std;
long long ans;
int n, k;
void ra(int sum, int c, int l){
    if(c == k - 1){
        if(n - sum >= l)
            ans ++;
        return;
    }
    for(int i = l; i <= (n - sum) - (k - c - 1); i ++)
        ra(sum + i, c + 1, i);
}
int main(int argc, char const *argv[])
{
    scanf("%d%d", &n, &k);
    ra(0, 0, 1);
    printf("%lld", ans);
    return 0;
}