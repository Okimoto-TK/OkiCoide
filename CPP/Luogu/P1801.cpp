#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
struct node{
    int lc;
    int rc;
    int vl;
    int sz;
    int cn;
    int pr;
};
int n, m, i, p, rt, j;
int a[200007];
int u[200007];
node t[200007];
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
        t[k].vl = v;
        t[k].sz = 1;
        t[k].cn = 1;
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
int get(int k, int v){
    if(v <= t[t[k].lc].sz){
        return get(t[k].lc, v);
    }
    else if(v <= t[t[k].lc].sz + t[k].cn){
        return t[k].vl;
    }
    else{
        return get(t[k].rc, v - t[t[k].lc].sz - t[k].cn);
    }
}
int main(){
    srand(time(0));
    scanf("%d%d", &m, &n);
    for(int x = 1; x <= m; x ++){
        scanf("%d", &a[x]);
    }
    for(int x = 0; x < n; x ++){
        scanf("%d", &u[x]);
    }
    for(int x = 1; x <= m; x ++){
        ins(rt, a[x]);
        while(u[j] == x){
            i ++;
            j ++;
            printf("%d\n", get(rt, i));
        }
    }
    return 0;
}
