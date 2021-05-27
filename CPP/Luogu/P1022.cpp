#include <stdio.h>
#include <string.h>
using namespace std;
int main(int argc, char const *argv[])
{
    char l[1024];
    char r[1024];
    scanf("%[^=]=%s", l, r);
    int coe = 0;
    int pos = 1;
    bool one = true;
    bool ltt = false;
    int aSum = 0;
    int bSum = 0;
    char c;
    for(int i = 0; i < (int)strlen(l); i ++){
        if('a' <= l[i] && l[i] <= 'z'){
            c = l[i];
            coe = one ? 1 : coe;
            ltt = true;
            one = false;
        }
        else if('0' <= l[i] && l[i] <= '9'){
            one = false;
            coe *= 10;
            coe += l[i] - '0';
        }
        else{
            if(ltt){
                aSum += coe * pos;
                ltt = false;
                one = true;
                pos = 1;
                coe = 0;
            }
            else{
                bSum += coe * pos;
                ltt = false;
                one = true;
                pos = 1;
                coe = 0;
            }
            if(l[i] == '+')
                pos = 1;
            else
                pos = -1;
        }
    }
    if(ltt){
        aSum += coe * pos;
        ltt = false;
        one = true;
        pos = 1;
        coe = 0;
    }
    else{
        bSum += coe * pos;
        ltt = false;
        one = true;
        pos = 1;
        coe = 0;
    }
    for(int i = 0; i < (int)strlen(r); i ++){
        if('a' <= r[i] && r[i] <= 'z'){
            c = r[i];
            coe = one ? 1 : coe;
            ltt = true;
            one = false;
        }
        else if('0' <= r[i] && r[i] <= '9'){
            one = false;
            coe *= 10;
            coe += r[i] - '0';
        }
        else{
            if(ltt){
                aSum += coe * pos * -1;
                ltt = false;
                one = true;
                pos = 1;
                coe = 0;
            }
            else{
                bSum += coe * pos * -1;
                ltt = false;
                one = true;
                pos = 1;
                coe = 0;
            }
            if(r[i] == '+')
                pos = 1;
            else
                pos = -1;
        }
    }
    if(ltt){
        aSum += coe * pos * -1;
        ltt = false;
        one = true;
        pos = 1;
        coe = 0;
    }
    else{
        bSum += coe * pos * -1;
        ltt = false;
        one = true;
        pos = 1;
        coe = 0;
    }
    bSum *= -1;
    printf("%c=%.3f", c, aSum == 0 || bSum == 0 ? 0 : double(bSum) / double(aSum));
    return 0;
}