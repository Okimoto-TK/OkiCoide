#include <cstdio>
#include <queue>
int c, r, n;
int sx, sy;
bool mp[60][60];
bool f[1005][60][60];
int ord[1005];
const int vec[][2] = {{0, 0}, {-1, 0}, {0, 1}, {1, 0}, {0, -1}};
struct node
{
	int x, y;
	int dir;
	node(int a, int b, int c)
	{
		x = a;
		y = b;
		dir = c;
	}
};
std::queue<node> q;
int main()
{
	scanf("%d%d", &c, &r);
	char buf[60];
	for(int i = 1; i <= c; i++)
	{
		scanf("%s", buf + 1);
		for(int j = 1; j <= r; j++)
		{
			if(buf[j] == 'X')
			{
				mp[i][j] = false;
			}
			else
			{
				mp[i][j] = true;
				if(buf[j] == '*')
				{
					f[0][i][j] = true;
				}
			}
		}
	}
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%s", buf);
		if(buf[0] == 'N') ord[i] = 1;
		if(buf[0] == 'E') ord[i] = 2;
		if(buf[0] == 'S') ord[i] = 3;
		if(buf[0] == 'W') ord[i] = 4;
		for(int x = 1; x <= c; x++)
		{
			for(int y = 1; y <= r; y++)
			{
				if(f[i - 1][x][y])
				{
					for(int _x = x + vec[ord[i]][0], _y = y + vec[ord[i]][1]; _x <= c && _x > 0 && _y <= r && _y > 0; _x += vec[ord[i]][0], _y += vec[ord[i]][1])
					{
						if(!mp[_x][_y]) break;
						f[i][_x][_y] = true;
					}
				}
			}
		}
	}
	for(int i = 1; i <= c; i++)
	{
		for(int j = 1; j <= r; j++)
		{
			if(!mp[i][j]) printf("X");
			else if(f[n][i][j]) printf("*");
			else printf(".");
		}
		putchar('\n');
	}
	return 0;
}
