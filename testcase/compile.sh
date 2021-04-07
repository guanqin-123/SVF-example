#!/bin/bash
for i in `ls ./testcase/src/*.c`
do 
    echo $i;
    $LLVM_DIR/bin/clang -S -c -Xclang -disable-O0-optnone -g -fno-discard-value-names -emit-llvm $i -o ./testcase/bc/${i:15}.ll
    $LLVM_DIR/bin/opt -S -mem2reg ./testcase/bc/${i:15}.ll -o ./testcase/bc/${i:15}.ll
done