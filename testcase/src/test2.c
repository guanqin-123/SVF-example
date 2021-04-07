#include<stdbool.h>
extern void sink(int* s);
int source(){
    return 1;
};
int main(){
        int a = 0;
        int num = 0;
        if( a <= 1 ){ // unary
                num = source();
        }
        sink(&num);
        return 0;
};