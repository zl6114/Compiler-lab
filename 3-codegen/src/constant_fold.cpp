#include "ast.hpp"

#include <cstdlib>
#include <fstream>

int main(int argc, char *argv[])
{
    if(argc<2){
        fprintf(stderr, "Usage : interpreter sourceCode [ arg0 [ arg1 [ ... ] ] ]\n");
        fprintf(stderr, "Missing sourceCode.\n");
        exit(1);
    }

    std::ifstream code(argv[1]);

    InterpretContext context;
    for(int i=2; i<argc; i++){
        context.params.push_back(atol(argv[i]));
    }
    TreePtr src=Parse(code);
    bool changed = false;
    PrettyPrint(std::cerr, src);
    std::cout << '\n';
    std::cout << '\n';
    Constant_fold(context, src,changed);
    PrettyPrint(std::cerr, src);
    //std::cout << "changed" << changed << '\n';
    if (changed = true){
        std::cout << "0" << '\n';
        return 0;
    }else{
        return 1;
        std::cout << "1" << '\n';
    }
}
