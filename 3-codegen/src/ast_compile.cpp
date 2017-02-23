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
        std::cout<<"output "<<(program->branches.at(0))->type<<"\n";
        CompileRec(destReg, program->branches.at(0));
    }else if(program->type=="Assign"){
        destReg = program->value;
        CompileRec(destReg, program->branches.at(0));
    }else if(program->type=="Add"){
        //if( regex_match( (program->branches.at(1))->type, reId ) ){
        //    std::cout<<"const "<<(program->branches.at(1))->type<<" "<<(program->branches.at(1))->type<<std::endl;
        //}
        std::cout<<"add "<<destReg<<" "<<(program->branches.at(0))->type
        <<" "<<(program->branches.at(1))->type<<std::endl;
    }else if(program->type=="Sub"){
        std::cout<<"sub "<<destReg<<" "<<(program->branches.at(0))->type
        <<" "<<(program->branches.at(1))->type<<std::endl;
    }else if(program->type=="LessThan"){

    }else if(program->type=="While"){
        //std::string top = "top";
        std::string top=makeName("top");
        //std::string bottom = "bottom";
        std::string bottom=makeName("bottom");
        std::cout <<":" << top << '\n';
        std::string zero = makeName("zero");
        std::cout<<"const "<<zero<<" 0"<<std::endl;
        std::cout << "beq " <<(program->branches.at(0))->type <<" "<<zero<<" "<<bottom<< '\n';
        CompileRec((program->branches.at(0))->type, (program->branches.at(1)));
        std::cout << "beq "<< zero << " " << zero << " " << top << '\n';
        std::cout <<":" <<bottom << '\n';
        CompileRec(destReg, program->branches.at(0));
    }else if(program->type=="If"){
        std::string ELSE=makeName("else");
        //std::string ELSE = "else";
        std::string JUMP=makeName("L1");
        //std::string JUMP = "L1";
        std::string zero = makeName("zero");
        std::cout<<"const "<<zero<<" 0"<<std::endl;
        CompileRec(destReg, program->branches.at(0));
        std::cout << "beq " <<destReg <<" "<<zero<<" "<<ELSE<< '\n';
        CompileRec(destReg, program->branches.at(1));
        std::cout << "beq " << zero <<" "<<zero<<" "<<JUMP<< '\n';
        std::cout << ":" << ELSE << '\n';
        CompileRec(destReg, program->branches.at(2));
        std::cout << ":" << JUMP << '\n';
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
