#include <stdio.h>
#include <algorithm>
using namespace std;
struct num
{
    int idx;
    int dat;
};
int mp;
bool cmp(num a, num b){
    if(a.dat == b.dat)
        return b.idx == mp;
    else
        return a.dat > b.dat;
}
int main(int argc, char const *argv[])
{
    int n;
    int max = -1;
    scanf("%d", &n);
    num s[n];
    num a[n];
    for(int i = 0; i < n; i ++){
        scanf("%d", &s[i].dat);
        s[i].idx = i;
    }
    for(int i = 0; i < n; i ++){
        scanf("%d", &a[i].dat);
        a[i].idx = i;
    }
    for(int i = 0; i < n; i ++)
        if(s[i].dat * 2 + a[i].dat > max){
            mp = i;
            max = s[i].dat * 2 + a[i].dat;
        }
    swap(a[0], a[mp]);
    sort(a + 1, a + n, cmp);
    int lst = s[mp].dat * 2;
    int dat = 0;
    for(int x = 0; x < n; x ++){
        if(s[x].dat > s[mp].dat){
            mp = x;
            lst = s[mp].dat * 2;
        }
        dat += a[x].dat;
        printf("%d\n", lst + dat);
    }
    return 0;
}