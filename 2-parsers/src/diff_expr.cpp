#include "ast.hpp"
#include <iomanip>

int main(int argc, char *argv[])
{
    //std::string s;
    //int i = 0;
    //bool num = true;
    //std::cout << argv[1] << argv[2] << std::endl;
    /*for(int i = 1; i < argc-1; i++){
        std::string s(argv[i]);
        const Expression *ast=parseAST();
        ast->differentiate(argv[i]);
        std::cout << s << '\n';
        std::cout << "+";
    }*/
    const Expression *ast=parseAST();
    for(int i = 1; i < argc; i++){
        ast->differentiate(argv[i]);
        //std::cout << i << '\n';
        if(i != argc-1){
            std::cout << " + ";
        }
    }


    std::cout<<std::endl;

    return 0;
}
