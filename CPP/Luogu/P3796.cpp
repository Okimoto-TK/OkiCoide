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
    vector <int> ex;
    node(){
        vl = 0;
        sp = 0;
        fl = 0;
        id = 0;
    }
};
int n, p = 1;
node t[20007];
char s[1000007];
char s_[207][107];
int b[1007];
queue <int> ans;
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
    t[k].id = x;
}
void pre(){
    queue <int> q;
    q.push(1);
    while(!q.empty()){
        int k = q.front();
        q.pop();
        int c = t[k].vl;
        for(int u = t[k].sp; u != 0; u = t[u].sp){
            int v = t[u].fl;
            if(t[v].ch[c]){
                t[k].fl = t[v].ch[c];
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
}
int getMax(int a, int b){
    return a > b ? a : b;
}
int req(){
    memset(b, 0, sizeof(b));
    int k = 1;
    int r = 0;
    int l = strlen(s);
    for(int i = 0; i < l; i ++){
        int c = s[i] - 'a';
        k = t[k].ch[c];
        for(int u = k; u != 1; u = t[u].fl){
            b[t[u].id] ++;
        }
    }
    int max = -1;
    for(int i = 1; i <= n; i ++){
        max = getMax(max, b[i]);
    }
    for(int i = 1; i <= n; i ++){
        if(b[i] == max){
            ans.push(i);
        }
    }
    return max;
}
int main(){
    scanf("%d", &n);
    while(n != 0){
        p = 1;
        memset(t, 0, sizeof(t));
        for(int i = 0; i < 26; i ++){
            t[0].ch[i] = 1;
        }
        for(int i = 1; i <= n; i ++){
            scanf("%s", s);
            strcpy(s_[i], s);
            con(i);
        }
        pre();
        scanf("%s", s);
        printf("%d\n", req());
        while(!ans.empty()){
            printf("%s\n", s_[ans.front()]);
            ans.pop();
        }
        scanf("%d", &n);
    }
}
