#include <stdio.h>
#include <stack>
using namespace std;
const char DICT[21] = "0123456789ABCDEFGHIJ";
stack <int> ans;
int n, base;
int abs(int a){
    return a > 0 ? a : -a;
}
int mod(int a, int p){
    return (a % p + abs(p)) % p; 
}
int main(int argc, char const *argv[])
{
    scanf("%d%d", &n, &base);
    printf("%d=", n);
    while(n){
        int t = mod(n, base);
        ans.push(t);
        n = (n - t) / base;
    }
    while(!ans.empty()){
        printf("%c", DICT[ans.top()]);
        ans.pop();
    }
    printf("(base%d)", base);
    return 0;
}