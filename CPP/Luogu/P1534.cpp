#include<stdio.h>
#include<algorithm>
using namespace std;
int a[100007];
int n;
int main(){
    scanf("%d", &n);
    int x, y;
    bool flag = true;
    int sum = 0;
    for(int i = 1; i <= n; i ++){
        scanf("%d%d", &x, &y);
        a[i] += x + y - 8;
        a[i + 1] = a[i];
        sum += a[i];
    }
    printf("%d", sum);
    return 0;
}
