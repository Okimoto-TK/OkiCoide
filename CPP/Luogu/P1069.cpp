#include <stdio.h>
#include <math.h>
#include <string.h>
using namespace std;
bool can;
int ans = 1e9;
int n;
int m1, m2;
int s[30007];
int cnt;
int _s[30007];
int getMin(int a, int b){
    return a < b ? a : b;
}
int getMax(int a, int b){
    return a > b ? a : b;
}
int main(int argc, char const *argv[])
{
    scanf("%d", &n);
    scanf("%d%d", &m1, &m2);
    int t = m1;
    for(int i = 2; i <= m1 && m1 != 1; i ++){
        if(m1 % i == 0)
            cnt ++;
        while(m1 % i == 0){
            s[i] ++;
            m1 /= i;
        }
    }
    if(m1 > 1){
        cnt ++;
        s[m1] ++;
    }
    for(int i = 0; i < n; i ++){
        memset(_s, 0, sizeof(_s));
        int si;
        scanf("%d", &si);
        //int _si = si;
        for(int j = 2; j < 30007 && j <= si && si != 1; j ++){
            while(si % j == 0){
                _s[j] ++;
                si /= j;
            }
        }
        if(si > 1 && si < 30007){
            _s[si] ++;
        }
        int mx = 0;
        bool hv = true;
        for(int j = 2; j <= t; j ++){
            if(s[j] > 0 && _s[j] == 0){
                hv = false;
                break;
            }
            if(_s[j] == 0)
                continue;
            mx = getMax(mx, (int)ceil(double(s[j] * m2) / double(_s[j])));
            if(mx > ans){
                hv = false;
                break;
            }
        }
        if(hv){
            can = true;
            ans = getMin(ans, mx);
        }
    }
    if(can)
        printf("%d", ans);
    else
        printf("-1");
    return 0;
}