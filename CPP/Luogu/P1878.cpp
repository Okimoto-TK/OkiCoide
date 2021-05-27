#include <stdio.h>
#include <queue>
#include <math.h>
using namespace std;
int n;
bool flg[200010];
struct pupil
{
	char gdr;
	int tech;
};
pupil p[200010];
struct ptnr
{
	int boy;
	int girl;
	int diff;
	bool operator< (const ptnr & a) const{
		if(diff == a.diff){
			int min = boy > girl ? girl : boy;
			int amin = a.boy > a.girl ? a.girl : a.boy;
			return min > amin;
		}
		return diff > a.diff;
	}
};
struct ptnr_
{
	bool operator() (ptnr a, ptnr b){
		if(b.diff == a.diff){
			int bmin = b.boy > b.girl ? b.girl : b.boy;
			int amin = a.boy > a.girl ? a.girl : a.boy;
			return amin > bmin;
		}
		return a.diff > b.diff;
	}
};
struct ans
{
	
};
priority_queue <ptnr, vector<ptnr>, ptnr_> heap;
queue <ptnr> q;
int main(int argc, char const *argv[])
{
	scanf("%d\n", &n);
	for(int i = 1; i <= n; i ++){
		scanf("%c", &p[i].gdr);
	}
	for(int i = 1; i <= n; i ++){
		scanf("%d", &p[i].tech);
	}
	for(int i = 1; i < n; i ++){
		if(p[i].gdr != p[i + 1].gdr){
			ptnr temp;
			temp.boy = p[i].gdr == 'B' ? i : i + 1;
			temp.girl = 2 * i + 1 - temp.boy;
			temp.diff = abs(p[temp.boy].tech - p[temp.girl].tech);
			heap.push(temp);
		}
	}
	int ans = 0;
	while(!heap.empty()){
		ptnr temp = heap.top();
		heap.pop();
		if(flg[temp.boy] || flg[temp.girl]){
			continue;
		}
		ans ++;
		flg[temp.boy] = true;
		flg[temp.girl] = true;
		q.push(temp);
		if(temp.boy > temp.girl){
			int l = temp.girl - 1;
			while(flg[l] && l >= 1)
				l --;
			if(l == 0)
				continue;
			int r = temp.boy + 1;
			while(flg[r] && r <= n)
				r ++;
			if(r == n + 1)
				continue;
			if(p[l].gdr != p[r].gdr){
				ptnr temp;
				temp.boy = p[l].gdr == 'B' ? l : r;
				temp.girl = p[r].gdr == 'G' ? r : l;
				temp.diff = abs(p[temp.boy].tech - p[temp.girl].tech);
				heap.push(temp);
			}
		}
		if(temp.boy < temp.girl){
			int r = temp.girl + 1;
			while(flg[r] && r >= 1)
				r ++;
			if(r == n + 1)
				continue;
			int l = temp.boy - 1;
			while(flg[l] && l <= n)
				l --;
			if(l == 0)
				continue;
			if(p[l].gdr != p[r].gdr){
				ptnr temp;
				temp.boy = p[l].gdr == 'B' ? l : r;
				temp.girl = p[r].gdr == 'G' ? r : l;
				temp.diff = abs(p[temp.boy].tech - p[temp.girl].tech);
				heap.push(temp);
			}
		}
	}
	printf("%d\n", ans);
	while(!q.empty()){
		ptnr temp = q.front();
		q.pop();
		int max = temp.boy > temp.girl ? temp.boy : temp.girl;
		int min = temp.boy < temp.girl ? temp.boy : temp.girl;
		printf("%d %d\n", min, max);
	}
	return 0;
}