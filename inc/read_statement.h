#ifndef read_statement_H
#define read_statement_H
#include <cstdio>
#include <string>
class read_statement{
public:
    std::string read(FILE *);
    std::string read_string(std::string,int,char);
    std::string splice(std::string,char,char);
   void skip_to(FILE *,std::string);
};

#endif // read_statement_H

