#include <stdio.h>
#include <queue>
#include <string>
using namespace std;

const int TWO[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384};
string unravel(int n){
	string ans = "";
	queue <int> q;
	while(n != 0){
		int ptr = 14;
		while(TWO[ptr] > n){
			ptr --;
		}
		q.push(ptr);
		n -= TWO[ptr];
	}
	while(q.size() != 0){
		ans += "2(";
		if(q.front() <= 1)
			ans += to_string(q.front());
		else
			ans += unravel(q.front());
		ans += ")";
		if(q.size() != 1){
			ans += "+";
		}
		q.pop();
	}
	return ans;
}
int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);
	string str = unravel(n);
	string ans;
	size_t pos;
	bool flg = false;
	do{
		if(flg)
			str.erase(pos, 3);
		else
			flg = true;
		pos = str.find("(1)");
	}while(pos != string::npos);
	printf("%s", str.c_str());
	return 0;
}