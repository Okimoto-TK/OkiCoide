#include <stdio.h>
#include <math.h>
using namespace std;
int n;
int sum;
int ans;
int main(int argc, char const *argv[])
{
    scanf("%d", &n);
    sum = (n + 1) * n / 2;
    for(int i = 2; i <= sqrt(sum); i ++){
        if(sum % i == 0){
            ans = i;
            break;
        }
    }
    if(ans == 0)
        printf("No");
    else{
        printf("Yes\n");
        printf("1 %d\n", ans);
        printf("%d ", n - 1);
        for(int i = 1; i <= n; i ++){
            if(ans == i)
                continue;
            printf("%d ", i);
        }
    }
    return 0;
}