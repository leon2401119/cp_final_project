#include "expr.h"
#include <iostream>
using namespace std;


/*expr::expr(){
    // another way to solve the bug is to new a meaningless node for p to point to whenever an expr is being created
    // by calling its default constructor (either intentionally or accidentally)
    // this way p->use will not cause seg fault

    p = new int_node(0);
}*/

expr::expr(int num){
	p = new int_node(num);
}

expr::expr(char op, expr &l, expr &r){
	p = new binary_node(op,l,r);
}

int expr::eval(){
	return p->eval();
}


expr& expr::operator=(const expr& rhs){
	(rhs.p->use)++;
	if(!(--(p->use)))
		delete p;
	p = rhs.p;
	return *this;
}


int_node::int_node(int num){
    value = num;
}

int int_node::eval(){
    return value;
}

binary_node::binary_node(char o, expr &lch, expr &rch):op(o),lchild(lch),rchild(rch){


    /*
        triggers segmentation fault if binary node is initialized this way
        supposed reason is that an expr object lchild is created first with default constructor
        which does not exist beforehand. So the expr_node* p is
        some random address pointing to some not allocated memory segment
        And when lchild=lch is executed, by the definition of copy constructor
        it will attempt to check p->use to see if the expr_node p was pointing to has another ref to it
        Since the pointed memory by p is never allocated, p->use triggers segmentation fault
    */

    /*
    op = o;
    lchild = lch;
    rchild = rch;
    */

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
