#include <stdio.h>
using namespace std;
bool c[100007];
int n, m;
int lowbit(int x){
    return x & (-x);
}
void upd(int x){
    for(; x <= n; x += lowbit(x))
        c[x] ^= 1;
}
bool sum(int x){
    bool r = false;
    for(; x; x -= lowbit(x)){
        r ^= c[x];
    }
    return r;
}
int main(int argc, char const *argv[])
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i ++){
        int t;
        scanf("%d", &t);
        if(t == 1){
            int l, r;
            scanf("%d%d", &l, &r);
            upd(l);
            upd(r + 1);
        }
        else{
            int _i;
            scanf("%d", &_i);
            printf("%d\n", sum(_i) ? 1 : 0);
        }
    }
    return 0;
}