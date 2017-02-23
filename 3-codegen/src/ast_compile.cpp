#include "ast.hpp"

#include <string>
#include <regex>
#include <sstream>

static int makeNameUnq=0;

static std::string makeName(std::string base)
{
    return "_"+base+"_"+std::to_string(makeNameUnq++);
}

void CompileRec(
    std::string destReg,    // The name of the register to put the result in
    TreePtr program
){
    std::regex reNum("^-?[0-9]+$");
    std::regex reId("^[a-z][a-z0-9]*$");

    if( regex_match( program->type, reNum ) ){
        std::cout<<"const "<<destReg<<" "<<program->type<<std::endl;
    }else if( regex_match( program->type, reId ) ){
        std::string zero = makeName("zero");
        std::cout<<"const "<<zero<<" 0"<<std::endl;
        std::cout<<"add "<<destReg<<" "<<program->type<<" "<<zero<<std::endl;
    }else if(program->type=="Param"){
        std::cout<<"param "<<destReg<<" "<<program->value<<std::endl;
    }else if(program->type=="Seq"){
        for(unsigned i=0; i<program->branches.size(); i++){
            CompileRec(destReg, program->branches[i]);
        }
    }else if(program->type=="Input"){
        std::cout<<"input "<<destReg<<std::endl;
    }else if(program->type=="Output"){
        std::string zero = makeName("zero");
        std::cout<<"const "<<zero<<" 0"<<std::endl;
        std::cout<<"add "<<destReg<<" "<<(program->branches.at(0))->type<<" "<<zero<<std::endl;
        std::cout << "" << '\n';
    }else if(program->type=="Assign"){
        destReg = program->value;
        CompileRec(destReg, program->branches.at(0));
    }else if(program->type=="Add"){
        std::cout<<"add "<<destReg<<" "<<(program->branches.at(0))->type
        <<" "<<(program->branches.at(1))->type<<std::endl;
    }else if(program->type=="Sub"){

    }else if(program->type=="LessThan"){

    }else if(program->type=="While"){

    }else if(program->type=="If"){

    }
    // TODO : handle the others
    else{
        throw std::runtime_error("Unknown construct '"+program->type+"'");
    }
}

void Compile(
    TreePtr program
){
    // Create a register to hold the final result
    std::string res=makeName("res");

    // Compile the whole thing
    CompileRec(res, program);

    // Put the result out
    std::cout<<"halt "<<res<<"\n";
}
