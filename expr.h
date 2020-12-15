#include <iostream>
using namespace std;

class expr_node{
	public:
		virtual ~expr_node(){}
		virtual int eval() = 0;
};

class int_node: expr_node{
	private:
		int value;
	public:
		int_node(int num);
		~int_node(){}
		int eval();
};

class binary_node: expr_node{
	private:
		char op;
		expr_node* lchild;
		expr_node* rchild;
	public:
		binary_node(char o, expr_node* lch, expr_node* rch);
		~binary_node();
		int eval();
};
