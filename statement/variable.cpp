#include <iostream>
#include <list>
#include <string>
using namespace std;
class variable
{
public:
    string name;
    int value;
    list<variable *> list_var;
    variable()
    {
        name="";
        value=0;
    }
    variable * list_search(string var)
    {
    for(list<variable *>::iterator it=list_var.begin();it!=list_var.end();it++)
    {
        if((*it)->name.compare(var)==0)
            return (*it);
    }
    return NULL;
    }
    //friend class expression;
};
