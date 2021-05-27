#include <stdio.h>
using namespace std;
int h[100007];
int t[100007];
int n;
int ra(int l, int r){
    bool con = false;
    int begin;
    int end;
    int rst = 0;
    for(register int i = l; i <= r; i ++){
        if(con){
            if(h[i] >= t[i]){
                rst += ra(begin, end);
                con = false;
            }
            else{
                h[i] ++;
                end = i;
            }
        }
        else{
            if(h[i] < t[i]){
                h[i] ++;
                con = true;
                begin = i;
                end = i;
            }
        }
    }
    if(con)
        rst += ra(begin, end);
    return rst + 1;
}
int main(int argc, char const *argv[])
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        scanf("%d", &t[i]);
    printf("%d", ra(0, n - 1) - 1);
    return 0;
}