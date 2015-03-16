#include <iostream>
#include <string>
#include <cstdlib>
#include "variable.cpp"
using namespace std;
class expression
{
public:
    int state;
    virtual int evaluate()=0;
};

class constant_expression:public expression
{
public:
    int key;
    int evaluate(){
            return key;
    }
};
class plus_expression:public expression
{
    public:
    expression *left_child;
    expression *right_child;
    int evaluate()
    {
        return left_child->evaluate() + right_child->evaluate();
    }
};

class negative_expression:public expression
{
    public:
    expression *left_child;
    expression *right_child;
    int evaluate()
    {
        return left_child->evaluate() - right_child->evaluate();
    }
};

class multiplication_expression:public expression
{
    public:
    expression *left_child;
    expression *right_child;
    int evaluate()
    {
        return left_child->evaluate() * right_child->evaluate();
    }

};
class divide_expression:public expression
{
    public:
    expression *left_child;
    expression *right_child;
    int evaluate()
    {
        int temp=right_child->evaluate();
        if(temp!=0)
            return left_child->evaluate() / temp;
        else
        {
            cout<<"Divide by zero, AAAAAarghhhhh....";
            return -9999;
        }
    }

};
class less_equalto:public expression
{
public:
    expression *left_child;
    expression *right_child;
    int evaluate()
    {
        return left_child->evaluate() <= right_child->evaluate();
    }
};
class greater_equalto:public expression
{
public:
    expression *left_child;
    expression *right_child;
    int evaluate()
    {
        return left_child->evaluate() >= right_child->evaluate();
    }
};

class equal_equalto:public expression
{
public:
    expression *left_child;
    expression *right_child;
    int evaluate()
    {
        return left_child->evaluate() == right_child->evaluate();
    }
};

class not_equalto:public expression
{
public:
    expression *left_child;
    expression *right_child;
    int evaluate()
    {
        return left_child->evaluate() != right_child->evaluate();
    }
};
class variable_expression:public expression
{
    public:
    variable* var_loc;
    string name;
    int evaluate()
    {
      if(var_loc->list_search(name)!=NULL)
	       return var_loc->list_search(name)->value;
	else
		return 0;
    }
};
class eval_expression:public expression
{
public:
    expression * tokenize(string s,variable *var_t)
    {
        int b=0;
        for(int i=0;i<s.length();i++)
        {
            if(s.find("+")>s.length() && s.find("-")>s.length() && s.find("*")>s.length() &&s.find("<=")>s.length() &&s.find(">=")>s.length() &&s.find("!=")>s.length()  &&s.find("==")>s.length() &&s.find("/")>s.length() )
            {
                    string temp_check=s.substr(0,s.length()).c_str();
                    if(!(temp_check[0]>='0' && temp_check[0]<='9'))
                    {
                        variable_expression *p = new variable_expression();
                        p->name = temp_check;
                        p->var_loc = var_t;
                        return p;
                    }
                    else
                    {
                        constant_expression *p=new constant_expression();
                        p->key=(atoi(s.substr(0,s.length()).c_str()));
                        return p;
                    }
            }
            if(s[i]=='(')
                b++;
            else if(s[i]==')')
                b--;
            else if(s[i]=='+')
            {
                if(b==1)
                {
                    plus_expression *p=new plus_expression();
                    /*cout<<"left + chid is "<<s.substr(1,i-1) <<endl;
                    cout<<"right + chid is "<<s.substr(i+1,s.length()-i-2) <<endl;*/
                    p->left_child=tokenize(s.substr(1,i-1) ,var_t);
                    p->right_child=tokenize(s.substr(i+1,s.length()-i-2),var_t);
                    return p;
                }
            }
            else if(s[i]=='-')
            {
                if(b==1)
                {
                    negative_expression *p=new negative_expression();
                    /*cout<<"left - chid is "<<s.substr(1,i-1) <<endl;
                    cout<<"right - chid is "<<s.substr(i+1,s.length()-i-2) <<endl;*/
                    p->left_child=tokenize(s.substr(1,i-1),var_t );
                    p->right_child=tokenize(s.substr(i+1,s.length()-i-2),var_t);
                    return p;
                }
            }
            else if(s[i]=='*')
            {
                if(b==1)
                {
                    multiplication_expression *p=new multiplication_expression();
                    /*cout<<"left - chid is "<<s.substr(1,i-1) <<endl;
                    cout<<"right - chid is "<<s.substr(i+1,s.length()-i-2) <<endl;*/
                    p->left_child=tokenize(s.substr(1,i-1) ,var_t);
                    p->right_child=tokenize(s.substr(i+1,s.length()-i-2),var_t);
                    return p;
                }
            }
             else if(s[i]=='/')
            {
                if(b==1)
                {
                    divide_expression *p=new divide_expression();
                    /*cout<<"left - chid is "<<s.substr(1,i-1) <<endl;
                    cout<<"right - chid is "<<s.substr(i+1,s.length()-i-2) <<endl;*/
                    p->left_child=tokenize(s.substr(1,i-1) ,var_t);
                    p->right_child=tokenize(s.substr(i+1,s.length()-i-2),var_t);
                    return p;
                }
            }
             else if(s[i]=='<' && s[i+1]=='=')
            {
                if(b==1)
                {
                    /*cout<<"left - chid is "<<s.substr(1,i-1) <<endl;
                    cout<<"right - chid is "<<s.substr(i+2,s.length()-i-4) <<endl;*/
                    less_equalto *p=new less_equalto();
                    p->left_child=tokenize(s.substr(1,i-1),var_t);
                    p->right_child=tokenize(s.substr(i+2,s.length()-i-4),var_t);
                    return p;
                }
            }
             else if(s[i]=='>' && s[i+1]=='=')
            {
                if(b==1)
                {
                   /* cout<<"left - chid is "<<s.substr(1,i-1) <<endl;
                    cout<<"right - chid is "<<s.substr(i+2,s.length()-i-4) <<endl;*/
                    greater_equalto *p=new greater_equalto();
                    p->left_child=tokenize(s.substr(1,i-1),var_t);
                    p->right_child=tokenize(s.substr(i+2,s.length()-i-4),var_t);
                    return p;
                }
            }
            else if(s[i]=='=' && s[i+1]=='=')
            {
                if(b==1)
                {
                    /*cout<<"left - chid is "<<s.substr(1,i-1) <<endl;
                    cout<<"right - chid is "<<s.substr(i+2,s.length()-i-4) <<endl;*/
                    equal_equalto *p=new equal_equalto();
                    p->left_child=tokenize(s.substr(1,i-1),var_t);
                    p->right_child=tokenize(s.substr(i+2,s.length()-i-4),var_t);
                  /*  cout<<"left - chid is "<<p->left_child->evaluate() <<endl;
                    cout<<"right - chid is "<<p->left_child->evaluate()<<endl;*/
                    return p;
                }
            }
             else if(s[i]=='!' && s[i+1]=='=')
            {
                if(b==1)
                {
                   /* cout<<"left - chid is "<<s.substr(1,i-1) <<endl;
                    cout<<"right - chid is "<<s.substr(i+2,s.length()-i-3) <<endl;*/
                    not_equalto *p=new not_equalto();
                    p->left_child=tokenize(s.substr(1,i-1),var_t);
                    p->right_child=tokenize(s.substr(i+2,s.length()-i-4),var_t);
                    return p;
                }
            }
        }
    }
    expression * main (string s,variable *v)
    {
        expression *exp;
        exp=tokenize(s,v);
        return exp;
    }
};
