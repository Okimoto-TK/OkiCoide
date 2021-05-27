#include <stdio.h>
using namespace std;
int n;
int a[10007];
int getMin(int a, int b){
    return a > b ? a : b;
}
int main(int argc, char const *argv[])
{
    bool rising = true;
    int last = -1;
    scanf("%d", &n);
    int inc = 0;
    int dec = 0;
    for(int i = 0; i < n; i ++){
        bool temp;
        int a;
        scanf("%d", &a);
        if(a == last)
            continue;
        if(a > last)
            temp = true;
        else
            temp = false;
        if(temp && !rising)
            inc ++;
        else if(!temp && rising)
            dec ++;
        rising = temp;
        last = a;
    }
    dec --;
    printf("%d", getMin(dec, inc));
    return 0;
}