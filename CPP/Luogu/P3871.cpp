#include <stdio.h>
#include <stdlib.h>
using namespace std;
struct node{
    int lc;
    int rc;
    int vl;
    int pr;
    int cn;
    int sz;
    node(){
        cn = sz = lc = rc = vl = pr = 0;
    }
};
node t[100007];
int n, m, p, rt;
void upd(int k){
    t[k].sz = t[t[k].lc].sz + t[t[k].rc].sz + t[k].cn;
}
void zig(int & k){
    int y = t[k].lc;
    t[k].lc = t[y].rc;
    t[y].rc = k;
    t[y].sz = t[k].sz;
    upd(k);
    k = y;
}
void zag(int & k){
    int y = t[k].rc;
    t[k].rc = t[y].lc;
    t[y].lc = k;
    t[y].sz = t[k].sz;
    upd(k);
    k = y;
}
void ins(int & k, const int v){
    if(k == 0){
        k = ++ p;
        t[k].lc = 0;
        t[k].rc = 0;
        t[k].sz = 1;
        t[k].cn = 1;
        t[k].vl = v;
        t[k].pr = rand();
        return;
    }
    t[k].sz ++;
    if(t[k].vl == v){
        t[k].cn ++;
    }
    else if(t[k].vl > v){
        ins(t[k].lc, v);
        if(t[t[k].lc].pr < t[k].pr){
            zig(k);
        }
    }
    else{
        ins(t[k].rc, v);
        if(t[t[k].rc].pr < t[k].pr){
            zag(k);
        }
    }
}
int ith(int k, int i){
    if(i <= t[t[k].lc].sz){
        return ith(t[k].lc, i);
    }
    else if(i <= t[t[k].lc].sz + t[k].cn){
        return t[k].vl;
    }
    else{
        return ith(t[k].rc, i - t[t[k].lc].sz - t[k].cn);
    }
}
int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i ++){
        int a;
        scanf("%d", &a);
        ins(rt, a);
    }
    scanf("%d", &m);
    for(int i = 0; i < m; i ++){
        char op[4];
        scanf("%s", op);
        if(op[0] == 'a'){
            int x;
            scanf("%d", &x);
            ins(rt, x);
            n ++;
        }
        else{
            int mid = (n % 2 == 0) ? (n / 2) : ((n + 1) / 2);
            printf("%d\n", ith(rt, mid));
        }
    }
    return 0;
}
