#include <stdio.h>
using namespace std;
int r, c, zr, zc;
char zone[64][64];
char alter[256][256];
int main(int argc, char const *argv[])
{
	scanf("%d %d %d %d", &r, &c, &zr, &zc);
	for(int i = 0; i < r; i ++)
		scanf("%s", zone[i]);
	for(int i = 0; i < r; i ++){
		for(int j = 0; j < c; j ++){
			char c = zone[i][j];
			for(int zi = 0; zi < zr; zi ++){
				for(int zj = 0; zj < zc; zj ++){
					alter[i * zr + zi][j * zc + zj] = c;
				}
			}
		}
		for(int zi = 0; zi < zr; zi ++){
			alter[i * zr + zi][zc * c] = '\0';
		}
	}
	for(int i = 0; i < zr * r; i ++)
		printf("%s\n", alter[i]);
	return 0;
}