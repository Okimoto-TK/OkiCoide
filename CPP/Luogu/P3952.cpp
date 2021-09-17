#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int t, ptr;
int stk[105];
int vab[105];
int vis[105];
int main()
{
	freopen("in.in", "r", stdin);
	int ans = 0;
	int max = 0;
	bool init = true;
	for(scanf("%d", &t); t != 0; max = std::max(max, stk[ptr])) {
		char c[5];
		if(scanf("%s", c) == EOF) {
			--t;
			if(ptr > 0 || max == 0x3f3f3f3f) { printf("ERR\n"); }
			else {
				printf("%s\n", max == ans ? "Yes" :"No");
			}
		}
		else if(isdigit(c[0])) {
			if(!init) {
				--t;
				if(ptr > 0 || max == 0x3f3f3f3f) { printf("ERR\n"); }
				else {
					printf("%s\n", ans == max ? "Yes" : "No");
				}
			}
			init = false;
			max = 0;
			ptr = 0;
			memset(vis, 0, sizeof(vis));
			memset(stk, 0, sizeof(stk));
			memset(vab, 0, sizeof(vab));
			char o[10];
			scanf("%s", o);
			if(o[2] == '1') {
				ans = 0;
			}
			else {
				int w = 0;
				int len = strlen(o);
				for(int i = 4; i < len - 1; i++) {
					w *= 10;
					w += o[i] - '0';
				}
				ans = w;
			}
		}
		else if(c[0] == 'F') {
			char var[2], l[5], r[5];
			scanf("%s%s%s", var, l, r);
			if(vis[var[0] - 'a']) {
				stk[++ptr] = -(0x3f3f3f3f);
				max = 0x3f3f3f3f;
			}
			else {
				vis[var[0] - 'a'] = true;
				if(l[0] == 'n') {
					if(r[0] == 'n') stk[ptr + 1] = stk[ptr];
					else stk[ptr + 1] = -(0x3f3f3f3f);
				}
				else {
					if(r[0] == 'n') stk[ptr + 1] = stk[ptr] + 1;
					else {
						int lnum = 0;
						int rnum = 0;
						int llen = strlen(l);
						int rlen = strlen(r);
						for(int i = 0; i < llen; i++) {
							lnum *= 10;
							lnum += l[i] - '0';
						}
						for(int i = 0; i < rlen; i++) {
							rnum *= 10;
							rnum += r[i] - '0';
						}
						if(lnum > rnum) stk[ptr + 1] = -(0x3f3f3f3f);
						else stk[ptr + 1] = stk[ptr];
					}
				}
				++ptr;
			}
			vab[ptr] = var[0] - 'a';
		}
		else if(c[0] == 'E') {
			if(ptr >= 1) vis[vab[ptr]] = false;
			if(--ptr < 0) max = 0x3f3f3f3f;
		}
	}
	return 0;
}
