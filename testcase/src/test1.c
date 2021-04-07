#include <string.h>
#include <stdio.h>
char *source(){
    // e.g. sql injection init
    static char initstr[25] = "select* From City ..";
    return initstr;
}

char *sink(char* s){
    return s;
}

int main(){
    char *injection = source();
    char *s = sink(injection);
    return 0;
}