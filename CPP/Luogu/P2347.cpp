#include <stdio.h>
using namespace std;
bool b[1007];
int h[6];
int main(int argc, char const *argv[])
{
    b[0] = true;
    int ans = 0;
    for(int i = 0; i < 6; i ++)
        scanf("%d", &h[i]);
    for(int u = 0; u <= h[0]; u ++){
        for(int v = 0; v <= h[1]; v ++){
            for(int w = 0; w <= h[2]; w ++){
                for(int x = 0; x <= h[3]; x ++){
                    for(int y = 0; y <= h[4]; y ++){
                        for(int z = 0; z <= h[5]; z ++){
                            int t = u + 2 * v + 3 * w + 5 * x + 10 * y + 20 * z;
                            if(!b[t]){
                                b[t] = true;
                                ans ++;
                            }
                        }
                    }
                }
            }
        }
    }
    printf("Total=%d", ans);
    return 0;
}