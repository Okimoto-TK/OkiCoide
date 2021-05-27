#include <stdio.h>
#include <string.h>
#include <set>
using namespace std;
set <long long> s;
const int MOD = 7102487;
const int p1 = 207;
const int p2 = 413;
int n;
char m[15007];
int getMax(int a, int b){
    return a > b ? a : b;
}
int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i ++){
        long long t1 = 0;
        long long t2 = 0;
        scanf("%s", m);
        for(int j = 0; j < strlen(m); j ++){
            t1 *= p1;
            t2 *= p2;
            t1 = (t1 % MOD + m[j]) % MOD;
            t2 = (t2 % MOD + m[j]) % MOD;
        }
        long long t = t1 * MOD + t2;
        s.insert(t);
    }
    printf("%d", s.size());
    return 0;
}
