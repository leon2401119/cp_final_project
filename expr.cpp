#include "expr.h"
#include <iostream>
using namespace std;


int_node::int_node(int num){
    value = num;
}

int int_node::eval(){
    return value;
}

binary_node::binary_node(char o, expr_node* lch, expr_node* rch){
    op = o;
    lchild = lch;
    rchild = rch;
}

binary_node::~binary_node(){
    delete lchild;
    delete rchild;
}

int binary_node::eval(){
    int l = lchild -> eval();
    int r = rchild -> eval();

    if(op=='+'){
        return l + r;
    }
    else if(op=='-'){
        return l-r;
    }
    else if(op=='*'){
        return l*r;
    }
    else
        return l/r;
}
