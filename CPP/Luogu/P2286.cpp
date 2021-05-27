#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
using namespace std;
struct node{
    int lc, rc, wt, pr, sz;
};
int rt, n, p, lf;
node t[1000007];
inline void upd(const int & k){
    t[k].sz = t[t[k].lc].sz + t[t[k].rc].sz + 1;
}
inline void zig(int & k){ // right-zig
    int y = t[k].lc; // record left
    t[k].lc = t[y].rc; // pick up left's right
    t[y].rc = k; // pull down k
    t[y].sz = t[k].sz;
    upd(k);
    k = y; // update y to the top
}
inline void zag(int & k){ // left-zag
    int y = t[k].rc; // recore right
    t[k].rc = t[y].lc; // pick up right's left
    t[y].lc = k; // pull down k
    t[y].sz = t[k].sz;
    upd(k);
    k = y; // update y to the top
}
/*
strategy 1:
    1.record the reverse one.
    2.pick up the reverse one's reverse
    3.pull down k
    4.update y to the top
*/
inline void ins(int & k, const int & v){
    if(k == 0){
        k = ++ p;
        t[k].wt = v;
        t[k].lc = 0;
        t[k].rc = 0;
        t[k].pr = rand() % 10000007;
        t[k].sz = 1;
        return;
    }
    t[k].sz ++;
    if(t[k].wt > v){
        ins(t[k].lc, v);
        if(t[t[k].lc].pr < t[k].pr){
            zig(k);
        }
    }
    else if(t[k].wt < v){
        ins(t[k].rc, v);
        if(t[t[k].rc].pr < t[k].pr){
            zag(k);
        }
    }
}
inline int pre(const int & v){
    int x = rt;
    int res = 0;
    while(x){
        if(t[x].wt <= v){
            res = t[x].wt;
            x = t[x].rc;
        }
        else{
            x = t[x].lc;
        }
    }
    return res;
}
inline int suf(const int & v){
    int x = rt;
    int res = 0;
    while(x){
        if(t[x].wt >= v){
            res = t[x].wt;
            x = t[x].lc;
        }
        else{
            x = t[x].rc;
        }
    }
    return res;
}
inline void del(int & k, const int & v){
    if(t[k].wt == v){
        if(t[k].lc == 0 || t[k].rc == 0){
            k = t[k].lc + t[k].rc;
        }
        else if(t[t[k].lc].pr < t[t[k].rc].pr){
            zig(k);
            del(k, v);
        }
        else{
            zag(k);
            del(k, v);
        }
        return;
    }
    t[k].sz --;
    if(t[k].wt > v){
        del(t[k].lc, v);
    }
    else{
        del(t[k].rc, v);
    }
}
/*
strategy 2:
    1.EndCon: x equals to 0
    2.left smaller, right greater
    3.children's priority should be larger than parent's
    4.otherwise, left right-zig, right left-zag
*/
int main(int argc, char const *argv[]) {
    int state;
    srand(time(0));
    long long ans = 0;
    int mod = 1000000;
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++){
        int op, v;
        scanf("%d%d", &op, &v);
        if(lf == 0){
            state = op;
            memset(t, 0, sizeof(t));
            p = 0;
            rt = 0;
        }
        if(op == state){
            ins(rt, v);
            lf ++;
        }
        else{
            int x = pre(v);
            int y = suf(v);
            if(y == 0 || (abs(x - v) <= abs(y - v)) && x != 0){
                ans = (ans + abs(x - v) % mod) % mod;
                del(rt, x);
            }
            else{
                ans = (ans + abs(y - v) % mod) % mod;
                del(rt, y);
            }
            lf --;
        }
    }
    printf("%lld", ans);
    return 0;
}
