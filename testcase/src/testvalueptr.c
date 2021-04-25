#include <string.h>
#include <stdio.h>
int source(){
    return 1; //value 
}

void sink(int* s){
}

int main(){
    int injection = source();
    sink(&injection);
    return 0;
}