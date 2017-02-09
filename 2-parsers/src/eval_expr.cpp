#include "ast.hpp"

#include <iomanip>

int main(int argc, char *argv[])
{
    std::map<std::string,double> bindings;

    for(int i = 1; i < argc -1; i = i+2){
        std::string s(argv[i]);
        std::cout << s << '\n';
        double tmp(atof(argv[i+1]));
        std::cout << tmp << '\n';
        bindings.insert(std::pair<std::string,double>(s,tmp));
    }

    std::cout << bindings["x"] << '\n';
    // TODO : for each pair of arguments:
    //  - read the variable name
    //  - parse the value
    //  - insert into the bindings map

    const Expression *ast=parseAST();

    double res=ast->evaluate(bindings);

    std::cout << std::setprecision(6);
    std::cout << std::fixed;
    std::cout << res << std::endl;
    // TODO : print out with 6 decimal digits of precision

    return 0;
}
