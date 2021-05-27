#include <stdio.h>
using namespace std;
int n;
char sqr[101][101];
bool sav[101][101];
const char SPL[] = {'y', 'i', 'z', 'h', 'o', 'n', 'g', '\0'};
const int DIR[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
bool dfs(int sts, int h, int v, int i){
    if(sts == 7)
        return true;
    if(h < 0 || v < 0)
        return false;
    if(h >= n || v >= n)
        return false;
    if(sqr[h][v] != SPL[sts])
        return false;
    bool rsp = dfs(sts + 1, h + DIR[i][0], v + DIR[i][1], i);
    sav[h][v] |= rsp;
    return rsp;
}
int main(int argc, char const *argv[])
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++){
        scanf("%s", sqr[i]);
    }
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++)
            for(int dir = 0; dir < 8; dir ++){
                dfs(0, i, j, dir);
            }
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++)
            if(sav[i][j])
                printf("%c", sqr[i][j]);
            else
                printf("*");
        printf("\n");
    }
    return 0;
}