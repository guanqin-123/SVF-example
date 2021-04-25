#include<stdbool.h>
extern void sink(int* s);
int source(int s){
    if ( s > 1 ){
        if ( s > 2){
            return 2;
        }
        return 1;
    }else{
        if ( s < -1 ){
            return -1;
        }
        return 0;
    }
};
int main(){
        int num = source(1);
        sink(&num);
        return 0;
};