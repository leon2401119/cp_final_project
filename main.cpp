#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include "expr.h"

using namespace std;

class token{
public:
    union value{
        int num;
        char op;
    } v;
    bool is_operand;

    token(int num){
        v.num = num;
        is_operand = true;
    }
    token(char op){
        v.op = op;
        is_operand = false;
    }
};


vector<token> in_to_post(vector<token> infix){
    stack<token> s;
    map<char,int> symbol_priority;
    map<char,int>::iterator iter;
    symbol_priority['('] = 3;
    symbol_priority['+'] = 1;
    symbol_priority['-'] = 1;
    symbol_priority['*'] = 2;
    symbol_priority['/'] = 2;
    symbol_priority[')'] = 0;

    vector<token> result;
    char top;
    int index = 0,priority,top_priority;
    for(int i=0;i<infix.size();i++){
        if(infix[i].is_operand){
            // cout << infix[i].v.num << " ";
            result.push_back(infix[i]);
        }
        else{
            iter = symbol_priority.find(infix[i].v.op);
            priority = iter -> second;
            while(!s.empty()){
                top = s.top().v.op;
                iter = symbol_priority.find(top);
                top_priority = (top == '(')? 0:iter->second;
                if(priority<=top_priority){
                    if(infix[i].v.op == ')' && top=='('){
                        s.pop();
                        break;
                    }
                    else{
                        // cout << s.top().v.op << " ";
                        result.push_back(s.top());
                        s.pop();
                    }
                }
                else
                    break;
            }
            if(infix[i].v.op != ')')
                s.push(infix[i]);
        }
    }
    while(!s.empty()){
        // cout << s.top().v.op << " ";
        result.push_back(s.top());
        s.pop();
    }

    return result;
}


expr make_tree(vector<token> postfix){
    stack<expr> token_list;
    expr t;
    expr oprnd1;
    expr oprnd2;
    for(int i=0;i<postfix.size();i++){
        if(postfix[i].is_operand){
            t = expr(postfix[i].v.num);
            token_list.push(t);
        }
        else{
            oprnd2=token_list.top();
            token_list.pop();
            oprnd1=token_list.top();
            token_list.pop();
            expr new_node(postfix[i].v.op, oprnd1, oprnd2);
            token_list.push(new_node);
        }
    }
    return token_list.top();
}


vector<token> tokenizer(string raw){
    vector<token> tokens;
    int len=raw.length(),t=0;
    bool r_int; // denotes currently reading an integer
    for(int i=0;i<len;i++){
        if(raw[i]>='0' && raw[i]<='9'){
            r_int = true;
            t=t*10+raw[i]-'0';
        }
        else{
            if(r_int){
                tokens.push_back(token(t));
                t=0;
                r_int = false;
            }
            if(raw[i]=='+' || raw[i]=='-' || raw[i]=='*' || raw[i]=='/' || raw[i]=='(' || raw[i]==')'){
                tokens.push_back(token(raw[i]));
            }
        }
    }
    if(r_int)
        tokens.push_back(token(t));
    return tokens;
}


int main(){

	/*
	int_node exp1 = int_node(1);
	int_node exp2 = int_node(2);
	binary_node exp3 = binary_node('+', (expr_node*)&exp1, (expr_node*)&exp2);
	cout << exp3.eval() << endl;
	*/

	/*
	// compile error "taking addr of temp"
	binary_node exp3 = binary_node("+", (expr_node*)&int_node(1), (expr_node*)&int_node(2));
	*/


	vector<token> tokens, postfix;
	string input;

	while(1){
        cout << ">>> ";


        getline(cin, input);
        tokens = tokenizer(input);
        // tokens = tokenizer("2+((3+4)*7)");
        postfix = in_to_post(tokens);
        expr expression = make_tree(postfix);
	cout << expression.eval() << endl;
	}
}
