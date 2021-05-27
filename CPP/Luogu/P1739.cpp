#include <stdio.h>
#include <string.h>
#include <stack>
using namespace std;
int st1;
int st2;
int cn1;
int cn2;
char s[300];
int main(){
    scanf("%s", s);
    int ans = 0;
    for(int i = 0; i < strlen(s); i ++){
        if(s[i] == '('){
            st1 ++;
        }
        if(s[i] == ')'){
            cn2 ++;
            if(st1){
                st1 --;
                ans ++;
            }
        }
    }
    printf("%s", st1 == 0 && st2 == 0 ? "YES" : "NO");
    return 0;
}
