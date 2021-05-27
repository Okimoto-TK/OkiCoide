#include <stdio.h>
using namespace std;
char mould[6][8]{
    "..+---+",
    "./   /|",
    "+---+ |",
    "|   | +",
    "|   |/.",
    "+---+.."
};
int m, n;
int a[64][64];
int getMax(int a, int b){
    return a > b ? a : b;
}
char c[1007][1007];
void draw(int x, int y){
    for(int i = x; i < 6 + x; i ++){
        for(int j = y; j < 7 + y; j ++){
            if(mould[i - x][j - y] == '.')
                continue;
            c[i][j] = mould[i - x][j - y];
        }
    }
}
int main(int argc, char const *argv[])
{
    scanf("%d%d", &m, &n);
    for(int i = 0; i < m; i ++){
        for(int j = 0; j < n; j ++){
            scanf("%d", &a[i][j]);
        }
    }
    int base_h = 0;
    int max_h = 0;
    int max_w = 0;
    for(int i = m - 1; i >= 0; i --){
        for(int j = 0; j < n; j ++){
            max_h = getMax(max_h, base_h + 3 * a[i][j] + 3);
            max_w = getMax(max_w, base_h + 4 * (j + 1) + 3);
        }
        base_h += 2;
    }
    for(int i = 0; i < max_h; i ++){
        for(int j = 0; j < max_w; j ++)
            c[i][j] = '.';
        c[i][max_w] = '\0';
    }
    for(int i = 0; i < m; i ++){
        for(int j = 0; j < n; j ++){
            int at_h = max_h - 2 * (m - i - 1) - 6;
            int at_w = 2 * (m - i - 1) + 4 * j;
            for(int k = 0; k < a[i][j]; k ++){
                draw(at_h, at_w);
                at_h -= 3;
            }
        }
    }
    for(int i = 0; i < max_h; i ++)
        printf("%s\n", c[i]);
    return 0;
}