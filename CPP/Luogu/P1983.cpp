#include <stdio.h>
#include <queue>
using namespace std;
int n, m;
int id[1007];
bool v[1007][1007];
int main(int argc, char const *argv[])
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i ++){
        int s;
        scanf("%d", &s);
        int begin;
        int end;
        scanf("%d", &begin);
        bool isA[1007] = {false};
        isA[begin] = true;
        for(int j = 1; j < s - 1; j ++){
            int a;
            scanf("%d", &a);
            isA[a] = true;
        }
        scanf("%d", &end);
        isA[end] = true;
        for(int j = begin; j <= end; j ++){
            if(isA[j]){
                for(int k = begin; k <= end; k ++){
                    if(!isA[k])
                        v[j][k] = true;
                }
            }
        }
    }
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++)
            if(v[j][i])
                id[i] ++;
    }
    int cnt = n;
    int ans = 1;
    while(cnt){
        queue <int> q;
        for(int i = 0; i < n; i ++)
            if(id[i] == 0){
                q.push(i);
                cnt --;
            }
        if(cnt == 0)
            break;
        ans ++;
        while(!q.empty()){
            for(int i = 0; i < n; i ++)
                if(v[q.front()][i]){
                    id[i] --;
                    v[q.front()][i] = false;
                }
            id[q.front()] = -1;
            q.pop();
        }
    }
    printf("%d", ans);
    return 0;
}