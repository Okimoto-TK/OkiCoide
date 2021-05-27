#include <stdio.h>
using namespace std;
int m, d;
int t;
int end = 1;
int s[1000007];
int getMax(int a, int b){
    return a > b ? a : b;
}
void add(int k, int l, int r, int x, int v){
    if(l > x || r < x)
        return;
    if(l == x && r == x){
        s[k] = v;
        return;
    }
    //printf("%d %d %d %d %d\n", k, l, r, x, v);
    int mid = (l + r) / 2;
    add(k * 2, l, mid, x, v);
    add(k * 2 + 1, mid + 1, r, x, v);
    s[k] = getMax(s[k * 2], s[k * 2 + 1]);
}
int ask(int k, int l, int r, int x, int y){
    if(x > r || y < l)
        return -100000000;
    if(x <= l && y >= r)
        return s[k];
    int mid = (l + r) / 2;
    return(getMax(ask(k * 2, l, mid, x, y), ask(k * 2 + 1, mid + 1, r, x, y)));
}
int main(int argc, char const *argv[])
{
    for(int i = 0; i < 1000007; i ++)
        s[i] = -100000000;
    scanf("%d%d", &m, &d);
    for(int i = 0; i < m; i ++){
        char c[4];
        scanf("%s", c);
        if(c[0] == 'Q'){
            int l;
            scanf("%d", &l);
            t = ask(1, 1, m, end - l, end - 1);
            printf("%d\n", t);
        }
        else{
            int n;
            scanf("%d", &n);
            add(1, 1, m, end ++, (t + n) % d);
        }
    }
    return 0;
}