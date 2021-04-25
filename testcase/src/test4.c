#include<stdbool.h>
extern void sink(int* s);
extern int source();
int main(){
        int num = source();
        int a = num + 4;
        int s = a - 2;
        sink(&s);
        
        return 0;
};