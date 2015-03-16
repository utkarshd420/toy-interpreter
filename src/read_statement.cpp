#include "../inc/read_statement.h"
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

string read_statement::read(FILE *fin)
{

    string ans="";
    char x=(char)fgetc(fin);
    while(x!=';' && x!='\n')
    {
        if(x==EOF)
            return "";
        ans=ans+""+x;
        x=fgetc(fin);
    }
    return ans;
}

string read_statement::read_string(string temp,int n,char sep)
{
    string ans="";
    for(int i=0;i<temp.length();i++)
    {
        if(temp[i]!=sep)
            ans+=temp[i];
        else
        {
            if(n--==0)
                break;
            else
                ans="";
        }
    }
    return ans;
}

string read_statement::splice(string temp,char startf,char endt)
{
    int flag=0;
    string ans="";
    //cout<<startf<<" "<<endt<<endl;
    for(int i=0;i<temp.length();i++)
    {
        if(temp[i]==endt && flag==1)
        {
             flag++;
             break;
        }
        else if(temp[i]==startf)
            flag++;
        else if(flag==1)
            ans+=temp[i];

    }
    if(flag!=2)
        return "Wrong parameters for function splice.Error occured\n";
    else
        return ans;
}
void read_statement::skip_to(FILE *fin,string upto)
{
    while(read(fin).compare(upto)!=0);
}
