#include <iostream>
#include <list>
//#include "variable.cpp"
#include <string>
#include "expression.cpp"
using namespace std;
class statement
{
    public:
    virtual void run_statement()=0;
};

class if_statement:public statement
{
public:
    expression * condition;
    list<statement *> if_true;
    list<statement *> if_false;
    void run_statement()
    {
        //cout<<"if is evaluated \n";
        if(condition->evaluate())
        {
            //cout<<"if true size"<<if_true.size()<<endl;
            for(list<statement *>::iterator it=if_true.begin();it!=if_true.end();it++)
            {
                (*it)->run_statement();
            }
        }
        else
        {
            //cout<<"if false size"<<if_false.size()<<endl;
            for(list<statement *>::iterator it=if_false.begin();it!=if_false.end();it++)
            {
                (*it)->run_statement();
            }
        }
    }
};

class while_statement:public statement
{
public:
    expression* condition;
    list<statement *> while_true;
    variable *table;
    void run_statement()
    {
        int i=0;
        while(condition->evaluate())
        {
           // cout<<"condition no. "<<while_true.size()<<endl;
            for(list<statement *>::iterator it=while_true.begin();it!=while_true.end();it++)
            {
                (*it)->run_statement();
         //       while_true.pop_front();
            }
        }
    }
};

class print_statement:public statement
{
public:
    string state;
    expression * expr;
    print_statement()
    {
        state="";
    }
    void run_statement()
    {
       // cout<<"Print statemenst par hai\n";
        //cout<<"running";
        if(state.length()>0)
            cout<<state;
        else
            cout<<expr->evaluate();
    }
};

class assignment_statement:public statement
{
public:
    expression * right;
    variable *left;
    assignment_statement()
    {
         left=new variable();
    }
   void run_statement()
    {
        //cout<<"evaluation of right is "<<right->evaluate()<<endl;
        left->value=right->evaluate();
    }
 };
 class mult_assignment_statement:public statement
 {
 public:
    expression * right;
    variable *left;
    mult_assignment_statement()
    {
         left=new variable();
    }
    void run_statement()
    {
        left->value=left->value * right->evaluate();
    }
 };
class faltoo:public statement{
public:
    void run_statement()
    {
        return;
    }
};
