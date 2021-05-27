#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
struct node{
    int wt;
    int lc;
    int rc;
    int cn;
    int sz;
    int pr;
};
int n, rt, p;
node t[100007];
void upd(int & k){
    t[k].sz = t[t[k].lc].sz + t[t[k].rc].sz + t[k].cn;
}
void zig(int & k){ // left up
    int y = t[k].lc;
    t[k].lc = t[y].rc;
    t[y].rc = k;
    t[y].sz = t[k].sz;
    upd(k);
    k = y;
    return;
}
void zag(int & k){ // right up
    int y = t[k].rc;
    t[k].rc = t[y].lc;
    t[y].lc = k;
    t[y].sz = t[k].sz;
    upd(k);
    k = y;
    return;
}
void ins(int & k, const int & v){
    if(k == 0){
        k = ++ p;
        t[k].sz = 1;
        t[k].lc = 0;
        t[k].rc = 0;
        t[k].wt = v;
        t[k].pr = rand();
        t[k].cn = 1;
        return;
    }
    t[k].sz ++;
    if(v == t[k].wt){
        t[k].cn ++;
        return;
    }
    if(v < t[k].wt){
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
    return;
}
int vth(int  k, int  v){
    if(v <= t[t[k].lc].sz){
        return vth(t[k].lc, v);
    }
    else if(v <= t[t[k].lc].sz + t[k].cn){
        return t[k].wt;
    }
    else{
        return vth(t[k].rc, v - t[t[k].lc].sz - t[k].cn);
    }
}
int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++){
        int a;
        scanf("%d", &a);
        ins(rt, a);
        if(i % 2 == 1){
            printf("%d\n", vth(rt, (i + 1) / 2));
        }
    }
    return 0;
}
