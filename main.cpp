#include <iostream>
#include <string>
#include <list>
#include "inc/read_statement.h"
#include "statement/statements.cpp"
#include "src/read_statement.cpp"       //Remove this while compiling in g++
using namespace std;
class main1{
public:
variable *var_try;
list<statement *> program;
read_statement scanner;
FILE *fin;
    main1()
    {
    fin=fopen("input.txt","r");
    var_try=new variable();
    }

string trim(string str,char ch)
{
    string str_temp="";
    for(int i=0;i<str.length();i++)
    {
        if(str[i]!=ch)
            str_temp+=str[i];
    }
    return str_temp;
}

void print()
{
    for(list<variable *>::iterator it=var_try->list_var.begin();it!=var_try->list_var.end();it++)
    {
        cout<<"list is ->> "<<(*it)->name<<" :: "<<(*it)->value<<"\t";
    }
    cout<<endl;
}
/**variable * list_search(string var)
{
    for(list<variable *>::iterator it=list_var.begin();it!=list_var.end();it++)
    {
        if((*it)->name.compare(var)==0)
            return (*it);
    }
    return NULL;
}*/
string get_var(string temp_right)
{
    //cout<<"temp right is "<<temp_right<<endl;
    string var_temp="";
    string temp_final="";
    for(int i=0;i<temp_right.length();i++)
    {
        if((temp_right[i]>= 'a' && temp_right[i]<='z'))
        {
            while((temp_right[i]>= 'a' && temp_right[i]<='z')||(temp_right[i]>= 'A' && temp_right[i]<='Z'))
            {
                        var_temp+=temp_right[i];
                        i++;
            }
                i--;
                char *temp=new char();
                sprintf(temp,"%d",var_try->list_search(var_temp)->value);
                temp_final+= string(temp);
                var_temp="";
        }
        else
        {
            temp_final+=temp_right[i];
        }
    }
   // cout<<"temp_final is"<<temp_final<<endl;
    return temp_final;
}

statement* create_statement(string temp)
{
    static int done_state=0;
    string operand1=""+scanner.read_string(temp,0,' ');
    //cout<<"operand1 is"<<operand1<<endl;
    string _operator="";
    /**Printing operation */
    if(operand1.compare("println")==0)
    {
        print_statement *p=new print_statement();
        p->state="\n";
        return p;
    }
    else if(operand1.compare("print")==0)
    {
        _operator=""+scanner.read_string(temp,1,' ');
        print_statement *p=new print_statement();
       // print();
        //cout<<"_operator is "<<_operator<<endl;
        if(_operator[0]=='"')
        {
            p->state=""+scanner.splice(temp,'"','"');
        }
        else
        {
            /** Assumption that print statement only has variables. Work needs to be done over here*/
            eval_expression *e;
            p->expr= e->main(_operator,var_try);
        }
        return p;
    }
    else if(operand1.compare("if")==0)
    {
        string _condition=""+scanner.read_string(temp,1,' ');
        //cout<<"condition is "<<_condition<<endl;
        _condition=trim(_condition,' ');
        //cout<<_condition<<endl;
        if_statement *if_state=new if_statement();
        eval_expression *e;
        if_state->condition=e->main(_condition,var_try);
        //cout<<"if check condition is :"<<_condition<<endl;
        //cout<<"boool is "<<if_state->condition->evaluate();
       /* if(if_state->condition->evaluate())
        {*/
            string p=scanner.read(fin);
            p=trim(p,'\t');
            while(p.compare("else")!=0)
            {
            	//cout<<"p is "<<p<<endl;
                if(p.compare("")!=0 && p.compare("\n")!=0)
                {
                    if_state->if_true.push_back(create_statement(p));
                }
                p=scanner.read(fin);
                p=trim(p,'\t');
            }
            //scanner.skip_to(fin,"fi");
        //}
        /*else
        {
            scanner.skip_to(fin,"else");*/
            p=scanner.read(fin);
            p=trim(p,'\t');
           // cout<<" p here is "<<p<<endl;
            while(p.compare("fi")!=0)
            {
                if(p.compare("")!=0 && p.compare("\n")!=0)
                    if_state->if_false.push_back(create_statement(p));
                p=scanner.read(fin);
                p=trim(p,'\t');
                //cout<<" p here is "<<p<<endl;
            }
        //}
        return if_state;
    }

    else if(operand1.compare("while")==0)
    {
        string _condition=""+scanner.read_string(temp,1,' ');
        _condition=trim(_condition,' ');
        while_statement *while_state=new while_statement();
        done_state++;
        eval_expression *e;
        while_state->condition=e->main(_condition,var_try);
        /*eval_expression *e;
        while_state->condition=_condition;*/
        while_state->table=var_try;
       /* if(while_state->condition->evaluate())
        {*/
            //done_state--;
            string p=scanner.read(fin);
            p=trim(p,'\t');
            while(p.compare("done")!=0)
            {
             //   cout<<" p in while is "<<p<<endl;
                if(p.compare("")!=0 && p.compare("\n")!=0)
                    while_state->while_true.push_back(create_statement(p));
                p=scanner.read(fin);
                p=trim(p,'\t');
            }
           //  cout<<" p in while is "<<p<<endl;
            //while_state->while_true.pop_back();
        //}
       /* else
        {
           // while(done_state--!=0)
                scanner.skip_to(fin,"done");
        }*/
        return while_state;
    }

    else if(operand1.find(":=")<=operand1.length())
    {
        string _left="";
        _left=scanner.read_string(temp,0,':');
        assignment_statement *as=new assignment_statement();
        //cout<<"left is "<<_left<<endl;
        as->left=var_try->list_search(_left);
        if(as->left!=NULL)
        {
            eval_expression *e;
            string temp_right=operand1.substr(operand1.find("=")+1);
            as->right=e->main(temp_right,var_try);
            /*
            as->left->value=as->right->evaluate();*/
        }
        else
        {
            variable *var=new variable();
            var->name= _left;
            var->value= 0;
            var_try->list_var.push_back(var);
            as->left=var;
            eval_expression *e;
            string temp_right=operand1.substr(operand1.find("=")+1);
           //cout<<"get_var "<<get_var(temp_right)<<endl;
           // print();
            as->right=e->main(temp_right,var_try);
            //as->left->value=as->right->evaluate();
        }
       // print();
        return as;
    }

    else if(operand1.find("*=")<=operand1.length())
    {
        string _left="";
        _left=scanner.read_string(temp,0,'*');
        mult_assignment_statement *as=new mult_assignment_statement();
        as->left=var_try->list_search(_left);
        if(as->left!=NULL)
        {
            eval_expression *e;
            string temp_right=operand1.substr(operand1.find("=")+1);
            as->right=e->main(temp_right,var_try);
        }
        else
        {
            variable *var=new variable();
            var->name= _left;
            var->value= 0;
            var_try->list_var.push_back(var);
            as->left=var;
            eval_expression *e;
            string temp_right=operand1.substr(operand1.find("=")+1);
           //cout<<"get_var "<<get_var(temp_right)<<endl;
           // print();
            as->right=e->main(temp_right,var_try);
            //as->left->value=as->right->evaluate();
        }
       // print();
        return as;
    }

    else                    //for skip done and other faltoo statements
    {
        faltoo * falt=new faltoo();
        return falt;
    }
}
int main()
{
     int line=0;
    while(!feof(fin))
    {
        //cout<<"started"<<endl;
        string temp=""+scanner.read(fin);
        temp=trim(temp,'\t');
        //cout<<"temp is "<<temp<<endl;
        if(temp.compare("")!=0 && temp.compare("\n")!=0)
        {
                 program.push_back(create_statement(temp));
                 //cout<<(int)temp[0]<<endl;
                 cout<<"line parsed is "<<line++<<endl;
                 //cout<<"list size is "<<program.size()<<endl;
                 //print();
        }
       // print();
        //cout<<endl;
    }
    cout<<"Reading done Running..."<<endl;
    for(list<statement *>::iterator it=program.begin();it!=program.end();it++)
    {
               //print();
                //  cout<<program.size()<<endl;
                (*it)->run_statement();
    }
}
};
int main()
{
    main1 *ob=new main1();
    ob->main();

}
