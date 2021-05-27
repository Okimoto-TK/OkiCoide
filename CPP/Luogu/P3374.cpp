#include <stdio.h>
using namespace std;
int n, m;
int c[1000007];
int lbt(int x){
    return (x & (-x));
}
void upd(int x, int k){
    for(; x <= n; x += lbt(x))
        c[x] += k;
}
int sum(int x){
    int r = 0;
    for(; x; x -= lbt(x))
        r += c[x];
    return r;
}
int main(int argc, char const *argv[])
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++){
        int v;
        scanf("%d", &v);
        upd(i, v);
    }
    for(int j = 0; j < m; j ++){
        int t;
        scanf("%d", &t);
        if(t == 1){
            int x, k;
            scanf("%d%d", &x, &k);
            upd(x, k);
        }
        else{
            int x, y;
            scanf("%d%d", &x, &y);
            printf("%d\n", sum(y) - sum(x - 1));
        }
    }
    return 0;
}