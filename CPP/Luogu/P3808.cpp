#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
#include <set>
using namespace std;
struct node{
    char vl;
    int ch[26];
    int sp;
    int dp;
    int fl;
    int as;
    node(){
        sp = 0;
        dp = 0;
        fl = 0;
        as = 0;
    }
};
int n, pool = 1;
char s[2000007];
node t[2000007];
bool b[2000007];
int main(){
    //freopen("in.in", "r", stdin);
    for(int i = 0; i < 26; i ++){
        t[0].ch[i] = 1;
    }
    scanf("%d", &n);
    for(int i = 0; i < n; i ++){
        scanf("%s", s);
        int k = 1;
        int len = strlen(s);
        for(int j = 0; j < len; j ++){
            char c = s[j];
            if(t[k].ch[c - 'a'] == 0){
                t[k].ch[c - 'a'] = ++ pool;
                t[pool].sp = k;
                t[pool].vl = c;
                t[pool].dp = j + 1;
            }
            k = t[k].ch[c - 'a'];
        }
        t[k].as += 1;
    }
    queue <int> q;
    q.push(1);
    while(!q.empty()){
        int k = q.front();
        q.pop();
        char c = t[k].vl;
        int u = t[k].sp;
        for(; u != 0; u = t[u].sp){
            int v = t[u].fl;
            if(t[v].ch[c - 'a']){
                t[k].fl = t[v].ch[c - 'a'];
                break;
            }
        }
        for(int i = 0; i < 26; i ++){
            if(t[k].ch[i]){
                q.push(t[k].ch[i]);
            }
            else{
                t[k].ch[i] = t[t[k].fl].ch[i];
            }
        }
    }
    scanf("%s", s);
    int k = 1;
    int ans = 0;
    int len = strlen(s);
    for(int i = 0; i <= len; i ++){
        char c = s[i];
        k = t[k].ch[c - 'a'];
        for(int u = k; u != 0 && !b[u]; u = t[u].fl){
            ans += t[u].as;
            t[u].as = 0;
            b[u] = true;
        }
    }
    printf("%d", ans);
    return 0;
}
