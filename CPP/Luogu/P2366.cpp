// By Sublime Text 3
// P2366, by Okimoto
// No copy, pls.
#include <stdio.h> // 标准输入输出
#include <map> // STL大法好b（￣▽￣）d　
#include <string> // 用string是因为string自带定义大小排序
#include <algorithm> // Sort
using namespace std;
int n;
map <string, int> mp; // 存输入的信息和数
string ans[128]; // 存储已输入的变量标识符 + 字典序排序
int ptr = 0; // ans的末尾下标记录变量，同时也是ans的长度
bool cmp(string a, string b){
	return a < b; // 字典序
}
int main(int argc, char const *argv[]){
	mp.insert(mp.begin(), pair<string, int>("__NULL__", 0)); // 对于a = b + c的代码处理a = b的情况时，将c假定成0
	scanf("%d\n", &n); // 输入n
	for(int i = 0; i < n; ++ i){
		char aa[32];
		char bb[32];
		scanf("%[^=]=", aa); // 输入直到遇见‘=’为止，顺便刷掉‘=’字符
		string a = aa;
		scanf("%[^;];\n", bb); // 刷掉‘；’ + 刷掉换行符
		string b = bb;
		if('0' <= b[0] && b[0] <= '9'){ // 若b变量是个数字类型的
			int sum = 0; // ‘+’字符之前的数
			int tmp = 0; // ‘+’字符之后的数
			int j;
			// 取sum
			for(j = 0; j < (int)b.size() && b[j] != '+'; j ++){
				sum *= 10;
				sum += b[j] - '0';
			}
			// 取tmp
			for(j = j + 1; j < (int)b.size(); j ++){
				tmp *= 10;
				tmp += b[j] - '0';
			}
			sum += tmp;
			if(mp.end() == mp.find(a)){ // 若a变量还未在mp中
				ans[ptr ++] = a; // ans记录a
				mp.insert(mp.begin(), pair<string, int>(a, sum)); // 将a推入mp
			}
			else
				mp[a] = sum; // 否则，将a的值改变
		}
		else{ // b变量是个变量类型的
			string x; // ‘+’字符之前的变量名
			string y; // ‘+’字符之后的变量名
			bool yFlg = true; // 判断是否没有‘+’以后的变量
			int j;
			// 取x
			for(j = 0; j < (int)b.size() && b[j] != '+'; j ++)
				x += b[j];
			// 取y
			for(j = j + 1; j < (int)b.size(); j ++){
				yFlg = false;
				y += b[j];
			}
			if(yFlg)
				y = "__NULL__";
			// 取数
			int sum = mp[x] + mp[y];
			//同理
			if(mp.end() == mp.find(a)){
				ans[ptr ++] = a;
				mp.insert(mp.end(), pair<string, int>(a, sum));
			}
			else
				mp[a] = sum;
		}
	}
	// 字典序排序
	sort(ans, ans + ptr, cmp);
	// 输出
	for(int i = 0; i < ptr; i ++)
		printf("%s %d\n", ans[i].c_str(), mp[ans[i]]);
	return 0;
}
// 谢谢大家阅读这篇题解，（づ￣3￣）づ╭❤～