#include<stdbool.h>
extern void sink(int* s);
extern int source();
int main(){
        int num = source();
        int a = num;
        a = num + 5;
        sink(&a);
        
        return 0;
};