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
    //std::cout << "changed is " << changed << '\n';
    TreePtr src=Parse(code);
    PrettyPrint(std::cerr, src);
    Dead_branches_removal(context, src,changed);
    //std::cout << "changed is " << changed << '\n';
    PrettyPrint(std::cerr, src);
    if(changed = true){
        return 0;
    }else{
        return 1;
    }
}
