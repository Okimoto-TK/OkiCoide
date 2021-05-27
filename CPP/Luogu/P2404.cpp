#include <stdio.h>
using namespace std;
int n;
int stk[10];
int ptr = 0;
void dfs(int sum){
    if(sum == n){
        for(int i = 0; i < ptr - 1; i ++)
            printf("%d+", stk[i]);
        printf("%d\n", stk[ptr - 1]);
        return;
    }
    if(sum > n)
        return;
    for(int i = stk[ptr - 1]; i < n; i ++){
        stk[ptr ++] = i;
        dfs(sum + i);
        ptr --;
    }
}
int main(int argc, char const *argv[])
{
    scanf("%d", &n);
    for(int i = 1; i < n; i ++){
        stk[ptr ++] = i;
        dfs(i);
        ptr --;
    }
    return 0;
}