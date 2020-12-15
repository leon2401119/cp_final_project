#include "expr.h"
#include <iostream>
using namespace std;


expr::expr(int num){
	p = new int_node(num);
}

expr::expr(char op, expr &l, expr &r){
	p = new binary_node(op,l,r);
}

int expr::eval(){
	return p->eval();	
}


/*expr& expr::operator=(const expr& rhs){
	p = rhs.p;
	return *this;
}*/


int_node::int_node(int num){
    value = num;
}

int int_node::eval(){
    return value;
}

binary_node::binary_node(char o, expr &lch, expr &rch){
    op = o;
    lchild = lch;
    rchild = rch;
}

binary_node::~binary_node(){
	/*
    delete lchild;
    delete rchild;
    */
}

int binary_node::eval(){
    int l = lchild.eval();
    int r = rchild.eval();

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
