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
    bool changed = false;
    TreePtr src=Parse(code);
    PrettyPrint(std::cerr, src);
    Constant_propagation(context, src, changed);
    PrettyPrint(std::cerr, src);
    if(changed = true){
        return 0;
    }else{
        return 1;
    }
}
