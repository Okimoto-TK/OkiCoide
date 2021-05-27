#include <stdio.h>
using namespace std;
int n, m;
int block[256][256];
long long less[256][256];
long long min = 10000000000000;
inline int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9') {
        if (c == '-')f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
void dfs(register int x, register int y, register bool used, register long long sum){
	if(x == m && y == m){
		if(sum < min)
			min = sum;
		return;
	}
	if(sum > min)
		return;
	if(y - 1 != 0){
		if(block[x][y - 1] == 0){
			if(used){
			    if(sum + 2 < less[x][y - 1]){
    				block[x][y - 1] = block[x][y];
			        less[x][y - 1] = sum + 2;
    				dfs(x, y - 1, false, sum + 2);
    				block[x][y - 1] = 0;
			    }
			}
		}
		else{
			if(block[x][y] != block[x][y - 1]){
			    if(sum + 1 < less[x][y - 1]){
			    	less[x][y - 1] = sum + 1;
				    dfs(x, y - 1, true, sum + 1);
				}
			}
			else{
			    if(sum < less[x][y - 1]){
			    	less[x][y - 1] = sum;
				    dfs(x, y - 1, true, sum);
				}
			}
		}
	}
	if(y != m){
		if(block[x][y + 1] == 0){
			if(used){
			    if(sum + 2 < less[x][y + 1]){
			    	less[x][y + 1] = sum + 2;
    				block[x][y + 1] = block[x][y];
    				dfs(x, y + 1, false, sum + 2);
    				block[x][y + 1] = 0;
			    }
			}
		}
		else{
			if(block[x][y] != block[x][y + 1]){
			    if(sum + 1 < less[x][y + 1]){
			    	less[x][y + 1] = sum + 1;
				    dfs(x, y + 1, true, sum + 1);
				}
			}
			else{
			    if(sum < less[x][y + 1]){
			    	less[x][y + 1] = sum;
				    dfs(x, y + 1, true, sum);
				}
			}
		}
	}
	if(x != m){
		if(block[x + 1][y] == 0){
			if(used){
			    if(sum + 2 < less[x + 1][y]){
			    	less[x + 1][y] = sum + 2;
    				block[x + 1][y] = block[x][y];
    				dfs(x + 1, y, false, sum + 2);
    				block[x + 1][y] = 0;
			    }
			}
		}
		else{
			if(block[x][y] != block[x + 1][y]){
			    if(sum + 1 < less[x + 1][y]){
			    	less[x + 1][y] = sum + 1;
				    dfs(x + 1, y, true, sum + 1);
				}
			}
			else{
			    if(sum < less[x + 1][y]){
			    	less[x + 1][y] = sum;
				    dfs(x + 1, y, true, sum);
				}
			}
		}
	}
	if(x - 1 != 0){
		if(block[x - 1][y] == 0){
			if(used){
			    if(sum + 2 < less[x - 1][y]){
			    	less[x - 1][y] = sum + 2;
    				block[x - 1][y] = block[x][y];
    				dfs(x - 1, y, false, sum + 2);
    				block[x - 1][y] = 0;
			    }
			}
		}
		else{
			if(block[x][y] != block[x - 1][y]){
			    if(sum + 1 < less[x - 1][y]){
			    	less[x - 1][y] = sum + 1;
				    dfs(x - 1, y, true, sum + 1);
				}
			}
			else{
			    if(sum < less[x - 1][y]){
			    	less[x - 1][y] = sum;
				    dfs(x - 1, y, true, sum);
				}
			}
		}
	}
}
int main(int argc, char const *argv[])
{
	for(int i = 0; i <= 100; i ++)
		for(int j = 0; j <= 100; j ++)
			less[i][j] = 1000000000;
	m = read();
	n = read();
	for(int i = 1; i <= n; i ++){
		int x, y, t;
		x = read();
		y = read();
		t = read();
		block[x][y] = t == 0 ? 2 : t;
	}
	less[1][1] = -1;
	dfs(1, 1, true, 0);
	if(min >= 1000000000){
		printf("-1\n");
		return 0;
	}
	printf("%lld", min);
	return 0;
}