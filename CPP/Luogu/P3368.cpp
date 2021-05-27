#include <stdio.h>
using namespace std;
int a[500007];
int c;
int n, m;
int lowbit(int x){
    return x & (-x);
}
void upd(int x, int k){
    for(; x <= n; x += lowbit(x))
        a[x] += k;
}
int sum(int x){
    int r = 0;
    for(; x; x -= lowbit(x))
        r += a[x];
    return r;
}
int main(int argc, char const *argv[])
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++){
        int v;
        scanf("%d", &v);
        upd(i, v - c);
        c = v;
    }
    for(int i = 0; i < m; i ++){
        int t;
        scanf("%d", &t);
        if(t == 1){
            int x, y, k;
            scanf("%d%d%d", &x, &y, &k);
            upd(x, k);
            upd(y + 1, -k);
        }
        else{
            int x;
            scanf("%d", &x);
            printf("%d\n", sum(x));
        }
    }
    return 0;
}