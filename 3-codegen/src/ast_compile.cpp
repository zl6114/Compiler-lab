#include "ast.hpp"

#include <string>
#include <regex>

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
        std::cout<<"add "<<program->type<<" "<<destReg<<" "<<zero<<std::endl;
    }else if(program->type=="Param"){
        std::cout<<"param "<<destReg<<" "<<program->value<<std::endl;
    }else if(program->type=="Seq"){
        for(unsigned i=0; i<program->branches.size(); i++){
            CompileRec(destReg, program->branches[i]);
        }
    }else if(program->type=="Input"){
        std::cout<<"input "<<destReg<<std::endl;
    }else if(program->type=="Output"){
        CompileRec(destReg, program->branches.at(0));
        std::cout<<"add "<<"_res_0"<<" "<<destReg<<" "<<"_zero_1"<<std::endl;
    }else if(program->type=="Assign"){
        CompileRec(destReg, program->branches.at(0));
    }else if(program->type=="Add"){
        std::string rDst = destReg;
        CompileRec(destReg, program->branches.at(0));
        std::string rA = destReg;
        CompileRec(destReg, program->branches.at(1));
        std::string rB = destReg;
        std::cout<<"add "<<rDst<<" "<<rA<<" "<<rB<<std::endl;
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
