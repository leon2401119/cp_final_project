#include <iostream>
using namespace std;

class expr_node;

class expr{
	friend class expr_node;
	expr_node* p;
	public:
		expr(){}
		expr(int);
		expr(char,expr&,expr&);
		~expr(){
			//delete p;
		};
		int eval();
		// expr& operator=(const expr& t);
};

class expr_node{
	friend class expr;
	public:
		virtual ~expr_node(){}
		virtual int eval() = 0;
};

class int_node: public expr_node{
	friend class expr;
	private:
		int value;
	public:
		int_node(int num);
		~int_node(){}
		int eval();
};

class binary_node: public expr_node{
	friend class expr;
	private:
		char op;
		expr lchild;
		expr rchild;
	public:
		binary_node(char o, expr &lch, expr &rch);
		~binary_node();
		int eval();
};
