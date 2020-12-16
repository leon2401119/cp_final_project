#include <iostream>
using namespace std;

class expr;

class expr_node{
        friend class expr;
        int use;
        public:
                expr_node():use(1){};
                virtual ~expr_node(){}
                virtual int eval() = 0;
};

class expr{
	friend class expr_node;
	expr_node* p;
	public:
		expr();
		expr(int);
		expr(char,expr&,expr&);
		~expr(){
			if((!--(p->use)))
				delete p;
		}
		int eval();
		expr(const expr& t){
			p = t.p;
			++p->use;
		}
		expr& operator=(const expr& t);
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
