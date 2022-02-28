#include <stdio.h>

int x=1;

void hengirmen(int a){
    if(a==64)
        x=2;
    else x=3;
}

void input(){
    char A[8];
    gets(A);
}


int main(){
    char x[15];
    gets(x);

    printf("%s",x);
}