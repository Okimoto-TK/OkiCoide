#include <stdio.h>
#include <string.h>
using namespace std;
int a[1007];
char s[1007];
int b[8];
int main(){
    a['1'] = 0;
    a['Q'] = 0;
    a['A'] = 0;
    a['Z'] = 0;
    a['2'] = 1;
    a['W'] = 1;
    a['S'] = 1;
    a['X'] = 1;
    a['E'] = 2;
    a['D'] = 2;
    a['C'] = 2;
    a['3'] = 2;
    a['4'] = 3;
    a['5'] = 3;
    a['R'] = 3;
    a['T'] = 3;
    a['G'] = 3;
    a['F'] = 3;
    a['V'] = 3;
    a['B'] = 3;
    a['6'] = 4;
    a['7'] = 4;
    a['Y'] = 4;
    a['U'] = 4;
    a['H'] = 4;
    a['J'] = 4;
    a['N'] = 4;
    a['M'] = 4;
    a['8'] = 5;
    a['I'] = 5;
    a['K'] = 5;
    a[','] = 5;
    a['9'] = 6;
    a['O'] = 6;
    a['L'] = 6;
    a['.'] = 6;
    a['0'] = 7;
    a['P'] = 7;
    a[';'] = 7;
    a['/'] = 7;
    a['='] = 7;
    a['-'] = 7;
    a['['] = 7;
    a[']'] = 7;
    a['\''] = 7;
    scanf("%s", s);
    for(int i = 0; i < strlen(s); i ++){
        b[a[s[i]]] ++;
    }
    for(int i = 0; i < 8; i ++){
        printf("%d\n", b[i]);
    }
    return 0;
}
