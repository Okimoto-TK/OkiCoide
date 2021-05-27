#include <stdio.h>
#include <string.h>
using namespace std;
struct bigInt
{
    int val[100007];
    int len;
    bigInt(){
        memset(val, 0, sizeof(val));
        val[1] = 1;
        len = 1;
    }
    void print(){
        for(int i = len; i >= 1; i --)
            printf("%d", val[i]);
    }
};
bigInt multi(bigInt a, int b){
    bigInt r;
    r.len = a.len;
    int x = 0;
    for(int i = 1; i <= a.len; i ++){
        r.val[i] = a.val[i] * b + x;
        x = r.val[i] / 10;
        r.val[i] %= 10;
    }
    if(x != 0){
        r.len ++;
        r.val[r.len] = x;
    }
    return r;
}
char n[64];
int base[10];
bool tar[10][10];
int k;
bigInt ans;
int main(int argc, char const *argv[])
{
    scanf("%s", n);
    scanf("%d", &k);
    for(int i = 0; i < 10; i ++){
        base[i] = 1;
        tar[i][i] = true;
    }
    for(int i = 0; i < k; i ++){
        int a, b;
        scanf("%d%d", &a, &b);
        tar[a][b] = true;
    }
    for(int t = 0; t < 100; t ++){
        for(int a = 0; a < 10; a ++){
            for(int b = 0; b < 10; b ++){
                if(!tar[a][b])
                    continue;
                for(int c = 0; c < 10; c ++){
                    if(tar[b][c])
                        tar[a][c] = true;
                }
            }
        }
    }
    for(int i = 0; i < 10; i ++){
        int cnt = 0;
        for(int j = 0; j < 10; j ++){
            if(tar[i][j])
                cnt ++;
        base[i] = cnt;
        }
    }
    for(int i = 0; i < (int)strlen(n); i ++)
        ans = multi(ans, base[n[i] - '0']);
    ans.print();
    return 0;
}