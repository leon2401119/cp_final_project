#include <iostream>
using namespace std;


class expr_node{
	public:
		expr_node();
		~expr_node();
		virtual int eval();
};

class int_node: public expr_node{
	private:
		int value;
	public:
		int_node(int num){
			value = num;
		}
		~int_node(){}
		int eval(){
			return value;
		}
};

class binary_node: public expr_node{
	private:
		string op;
		expr_node* lchild;
		expr_node* rchild;
	public:
		binary_node(string o, expr_node* lch, expr_node* rch){
			op = o;
			lchild = lch;
			rchild = rch;
		}
		~binary_node(){
			delete lchild;
			delete rchild;
		}
		int eval(){
			int l = lchild -> eval();
			int r = rchild -> eval();

			if(op=="+"){
				return l + r;
			}
			else if(op=="-"){
				return l-r;
			}
			else if(op=="*"){
				return l*r;
			}
			else
				return l/r;
		}
};

int main(){
	/*
	expr_node *exp = &binary_node("+",&int_node(1),&int_node(2));
	*/
	int_node exp1 = int_node(1);
	int_node exp2 = int_node(2);
	binary_node exp3 = binary_node("+", &exp1, &exp2);
	cout << exp3.eval();
}
