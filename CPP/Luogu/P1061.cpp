#include <stdio.h>
using namespace std;
int s, t, w;
char in[32];
int p[32];
char dict[32];
int main(int argc, char const *argv[])
{
    scanf("%d%d%d", &s, &t, &w);
    int _w = t - s;
    for(int i = 0; i <= _w; i ++){
        dict[i] = s - 1 + i + 'a';
    }
    scanf("%s", in);
    for(int i = 0; i < w; i ++)
        p[i] = in[i] - 'a' - s + 1;
    for(int i = 0; i < 5; i ++){
        if(p[w - 1] != _w)
            p[w - 1] += 1;
        else{
            int j;
            for(j = w - 1; j >= 0; j --){
                if(p[j] < _w - (w - j) + 1)
                    break;
                if(j == 0)
                    return 0;
            }
            p[j] += 1;
            for(int k = j + 1; k < w; k ++)
                p[k] = p[k - 1] + 1;
        }
        for(int j = 0; j < w; j ++)
            printf("%c", dict[p[j]]);
        printf("\n");
    }
    return 0;
}