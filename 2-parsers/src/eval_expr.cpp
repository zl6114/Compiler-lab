#include "ast.hpp"

#include <iomanip>

int main(int argc, char *argv[])
{
    std::map<std::string,double> bindings;
    
    for(int i = 0; i < argc; i = i+2){
        map(argv[i])
    }
    // TODO : for each pair of arguments:
    //  - read the variable name
    //  - parse the value
    //  - insert into the bindings map

    const Expression *ast=parseAST();

    double res=ast->evaluate(bindings);

    // TODO : print out with 6 decimal digits of precision

    return 0;
}
