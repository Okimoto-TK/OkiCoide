#include <stdio.h>
using namespace std;
int n, m;
int a[1000007];
int s[1000007];
bool t[1000007];
void _xor_(int k, int l, int r){
    s[k] = (r - l + 1) - s[k];
    t[k] ^= true;
}
void psh(int k, int l, int r){
    if(t[k]){
        int mid = (l + r) / 2;
        _xor_(k * 2, l, mid);
        _xor_(k * 2 + 1, mid + 1, r);
        s[k] = s[k * 2] + s[k * 2 + 1];
        t[k] = false;
    }
}
void con(int k, int l, int r){
    if(l == r){
        s[k] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    con(k * 2, l, mid);
    con(k * 2 + 1, mid + 1, r);
    s[k] = s[k * 2] + s[k * 2 + 1];
}
void pro(int k, int l, int r, int x, int y){
    if(l >= x && r <= y){
        _xor_(k, l, r);
        return;
    }
    psh(k, l, r);
    int mid = (l + r) / 2;
    if(x <= mid)
        pro(k * 2, l, mid, x, y);
    if(y > mid)
        pro(k * 2 + 1, mid + 1, r, x, y);
    s[k] = s[k * 2] + s[k * 2 + 1]; 
}
int req(int k, int l, int r, int x, int y){
    if(l >= x && r <= y){
        return s[k];
    }
    psh(k, l, r);
    int res = 0;
    int mid = (l + r) / 2;
    if(x <= mid)
        res += req(k * 2, l, mid, x, y);
    if(y > mid)
        res += req(k * 2 + 1, mid + 1, r, x, y);
    return res;
}
int main(int argc, char const *argv[])
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++)
        scanf("%1d", &a[i]);
    con(1, 1, n);
    for(int i = 0; i < m; i ++){
        int op;
        int l, r;
        scanf("%d%d%d", &op, &l, &r);
        if(op == 1)
            printf("%d\n", req(1, 1, n, l, r));
        else
            pro(1, 1, n, l, r);
    }
    return 0;
}