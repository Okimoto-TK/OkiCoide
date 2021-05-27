#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
struct pos
{
    int x;
    int y;
    int w[4];
};
int getMin(int a, int b){
    return a < b ? a : b;
}
const int INF = 0x3f3f3f3f;
int n;
int f[128][128][4]; // 0 refers to up, 1 refers to right, etc.
char a[128][128];
bool b[128][128];
pos s;
pos t;
queue <pos> q;
int main(int argc, char const *argv[])
{
    scanf("%d\n", &n);
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            scanf("%c", &a[i][j]);
            while(a[i][j] == ' ' || a[i][j] == 10 || a[i][j] == 13)
                scanf("%c", &a[i][j]);
        }
    }
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            if(a[i][j] == 'A'){
                s.x = i;
                s.y = j;
                for(int i = 0; i < 4; i ++)
                    s.w[i] = 0;
            }
            if(a[i][j] == 'B'){
                t.x = i;
                t.y = j;
            }
        }
    }
    memset(f, 0x3f, sizeof(f));
    q.push(s);
    while(!q.empty()){
        pos u = q.front();
        bool is = false;
        q.pop();
        for(int i = 0; i < 4; i ++){
            if(f[u.x][u.y][i] > u.w[i]){
                is = true;
                f[u.x][u.y][i] = u.w[i];
            }
        }
        if(is){
            if(u.x != 0){
                pos v;
                v.x = u.x - 1;
                v.y = u.y;
                for(int i = 0; i < 4; i ++)
                    v.w[i] = INF;
                if(a[v.x][v.y] != 'x'){
                    for(int i = 0; i < 4; i ++){
                        int j = 3;
                        int w = u.w[j] + (i != j ? 1 : 0);
                        v.w[i] = getMin(v.w[i], w);
                    }
                    q.push(v);
                }
            }
            if(u.y != 0){
                pos v;
                v.y = u.y - 1;
                v.x = u.x;
                for(int i = 0; i < 4; i ++)
                    v.w[i] = INF;
                if(a[v.x][v.y] != 'x'){
                    for(int i = 0; i < 4; i ++){
                        int j = 0;
                        int w = u.w[j] + (i != j ? 1 : 0);
                        v.w[i] = getMin(v.w[i], w);
                    }
                    q.push(v);
                }
            }
            if(u.x != n - 1){
                pos v;
                v.x = u.x + 1;
                v.y = u.y;
                for(int i = 0; i < 4; i ++)
                    v.w[i] = INF;
                if(a[v.x][v.y] != 'x'){
                    for(int i = 0; i < 4; i ++){
                        int j = 1;
                        int w = u.w[j] + (i != j ? 1 : 0);
                        v.w[i] = getMin(v.w[i], w);
                    }
                    q.push(v);
                }
            }
            if(u.y != n - 1){
                pos v;
                v.y = u.y + 1;
                v.x = u.x;
                for(int i = 0; i < 4; i ++)
                    v.w[i] = INF;
                if(a[v.x][v.y] != 'x'){
                    for(int i = 0; i < 4; i ++){
                        int j = 2;
                        int w = u.w[j] + (i != j ? 1 : 0);
                        v.w[i] = getMin(v.w[i], w);
                    }
                    q.push(v);
                }
            }
        }
    }
    int ans = INF;
    for(int i = 0; i < 4; i ++)
        ans = getMin(ans, f[t.x][t.y][i]);
    printf("%d\n", ans == INF ? -1 : ans);
    return 0;
}