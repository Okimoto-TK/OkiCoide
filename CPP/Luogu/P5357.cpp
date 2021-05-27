#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
struct node{
    int vl;
    int sp;
    int fl;
    int id;
    int ch[26];
    vector <int> v;
    node(){
        vl = 0;
        sp = 0;
        fl = 0;
        id = 0;
    }
};
int n, p = 1;
node t[200007];
char s[2000007];
int b[200007];
int as[200007];
int to[200007];
void con(int x){
    int k = 1;
    int l = strlen(s);
    for(int i = 0; i < l; i ++){
        int c = s[i] - 'a';
        if(t[k].ch[c] == 0){
            t[k].ch[c] = ++ p;
            t[p].sp = k;
            t[p].vl = c;
        }
        k = t[k].ch[c];
    }
    if(t[k].id){
        to[x] = t[k].id;
    }
    else{
        to[x] = x;
        t[k].id = x;
    }
}
void pre(){
    queue <int> q;
    q.push(1);
    while(!q.empty()){
        int k = q.front();
        q.pop();
        int c = t[k].vl;
        for(register int u = t[k].sp; u != 0; u = t[u].sp){
            int v = t[u].fl;
            if(t[v].ch[c]){
                t[k].fl = t[v].ch[c];
                t[t[k].fl].v.push_back(k);
                break;
            }
        }
        for(register int i = 0; i < 26; i ++){
            if(t[k].ch[i]){
                q.push(t[k].ch[i]);
            }
            else{
                t[k].ch[i] = t[t[k].fl].ch[i];
            }
        }
    }
}
void req(){
    int k = 1;
    int r = 0;
    int l = strlen(s);
    for(int i = 0; i < l; i ++){
        int c = s[i] - 'a';
        k = t[k].ch[c];
        b[k] ++;
    }
}
int dfs(int u){
    int r = b[u];
    for(int i = 0; i < t[u].v.size(); i ++){
        r += dfs(t[u].v[i]);
    }
    as[t[u].id] = r;
    return r;
}
int main(){
    scanf("%d", &n);
    for(int i = 0; i < 26; i ++){
        t[0].ch[i] = 1;
    }
    for(int i = 1; i <= n; i ++){
        scanf("%s", s);
        con(i);
    }
    pre();
    scanf("%s", s);
    req();
    dfs(1);
    for(int i = 1; i <= n; i ++){
        printf("%d\n", as[to[i]]);
    }
    return 0;
}
