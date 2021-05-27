#include<stdio.h>
#include<string.h>
#include<stack>
using namespace std;
//stack <int> nm;
int nmp;
int nm[1000007];
int opp;
int op[1000007];
//stack <int> op;
char s[2000007];
int x[1000007];
int st[1000007];
int n;
int q;
bool eff[1000007];
bool abs[1000007];
inline int read() {//快读
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9') {
        if (c == '-')f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
bool find(int a){
    if(abs[a])
        return true;
    if(st[a] == a){
        return eff[a];
    }
    if(!eff[a]){
        return false;
    }
    eff[a] = find(st[a]) && eff[a];
    abs[a] = eff[a];
    return eff[a];
}
int getAnd(int a, int b){
    return a == 1 && b == 1 ? 1 : 0;
}
int getOr(int a, int b){
    return a == 1 || b == 1 ? 1 : 0;
}
void init(){
    for(int i = 0; i < 1000007; i ++){
        st[i] = i;
    }
}
void proc(){
    if(op[opp - 1] == '!'){
        opp --;
        int t = nm[nmp - 1];
        x[t] = x[t] == 0 ? 1 : 0;
    }
    else if(op[opp - 1] == '&'){
        opp --;
        int a = nm[nmp - 1];
        nmp --;
        int b = nm[nmp - 1];
        nmp --;
        if(x[b] == 1){
            eff[a] = true;
        }
        if(x[a] == 1){
            eff[b] = true;
        }
        x[++ n] = getAnd(x[a], x[b]);
        st[a] = n;
        st[b] = n;
        nm[nmp] = n;
        nmp ++;
    }
    else{
        opp --;
        int a = nm[nmp - 1];
        nmp --;
        int b = nm[nmp - 1];
        nmp --;
        if(x[a] == 0){
            eff[b] = true;
        }
        if(x[b] == 0){
            eff[a] = true;
        }
        x[++ n] = getOr(x[a], x[b]);
        st[a] = n;
        st[b] = n;
        nm[nmp] = n;
        nmp ++;
    }
}
void calc(){
    int num = 0;
    int len = strlen(s);
    for(int i = 0; i < len; i ++){
        if(s[i] <= '9' && s[i] >= '0'){
            num *= 10;
            num += s[i] - '0';
        }
        else if(s[i] == ' ' && num > 0){
            nm[nmp] = num;
            nmp ++;
            num = 0;
        }
        else if(s[i] == '&' || s[i] == '!' || s[i] == '|'){
            op[opp] = s[i];
            opp ++;
            proc();
        }
    }
}
int main(){
    //freopen("expr.in", "r", stdin);
    //freopen("expr.out", "w", stdout);
    init();
    scanf("%[^\n]", s);
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++){
        scanf("%d", &x[i]);
    }
    calc();
    eff[nm[nmp - 1]] = true;
    abs[nm[nmp - 1]] = true;
    int ans = x[nm[nmp - 1]];
    scanf("%d", &q);
    for(int i = 0; i < q; i ++){
        int a = read();
        if(find(a)){
            printf("%d\n", ans == 0 ? 1 : 0);
        }
        else{
            printf("%d\n", ans);
        }
    }
    return 0;
}
