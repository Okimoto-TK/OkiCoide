#include <stdio.h>
using namespace std;
int n;
int main(int argc, char const *argv[])
{
	scanf("%d\n", &n);
	int a = 0;
	int d = 0;
	for(int i = 0; i < n; i ++){
		char c;
		scanf("%c", &c);
		if(c == 'A')
			a ++;
		else
			d ++;
	}
	printf("%s", a == d ? "Friendship" : (a > d ? "Anton" : "Danik"));
	return 0;
}