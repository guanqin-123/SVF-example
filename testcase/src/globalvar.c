#include <string.h>
#include <stdio.h>
extern int source();

void sink(int s){}

int main(){
    int injection = source();
    injection = 5;
    injection = 6;
    sink(injection);
    return 0;
}