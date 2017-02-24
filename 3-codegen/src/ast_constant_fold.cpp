#include "ast.hpp"

#include <regex>
#include <cstdlib>
#include <fstream>
#include <string>


int32_t Constant_fold(
    InterpretContext &context, // Contains the parameters and variable bindings
    TreePtr program,
    bool changed
){
    std::regex reNum("^-?[0-9]+$");
    std::regex reId("^[a-z][a-z0-9]*$");

    if( regex_match(program->type, reNum) ){
        return std::atol(program->type.c_str());
    // TODO : Check for things matching reId
    }else if( regex_match(program->type, reId) ){
        return (context.bindings[program->type]);
    }else if(program->type=="Param"){
        unsigned index=atol(program->value.c_str());
        auto value=context.params.at(index);
        return value;
    }else if(program->type=="Input"){
        int32_t val;
        std::cin>>val;
        return val;
    }else if(program->type=="Output"){
        int32_t val=Constant_fold(context, program->branches.at(0),changed);
    }else if(program->type=="Seq"){
        int32_t val;
        for(unsigned i=0; i<program->branches.size(); i++){
            val = Constant_fold(context, program->branches[i],changed);
        }
    }else if(program->type=="Assign"){
        int32_t val=Constant_fold(context, program->branches.at(0),changed);
        context.bindings[program->value] = val;
        return val;
    }else if(program->type=="Add"){
        if((regex_match((program->branches.at(0))->type, reNum))
        &&(regex_match((program->branches.at(0))->type, reNum))){
            int32_t val1 = Constant_fold(context, program->branches.at(0),changed);
            int32_t val2 = Constant_fold(context, program->branches.at(1),changed);
            program->branches.clear();
            std::string s = std::to_string(val1+val2);
            program->type = s;
            changed = true;
            //std::cout << "changde" << changed << '\n';
        }
        int32_t val1 = Constant_fold(context, program->branches.at(0),changed);
        int32_t val2 = Constant_fold(context, program->branches.at(1),changed);
    }else if(program->type=="Sub"){
        if((regex_match((program->branches.at(0))->type, reNum))
        &&(regex_match((program->branches.at(0))->type, reNum))){
            int32_t val1 = Constant_fold(context, program->branches.at(0),changed);
            int32_t val2 = Constant_fold(context, program->branches.at(1),changed);
            program->branches.clear();
            std::string s = std::to_string(val1-val2);
            program->type = s;
            changed = true;
            //std::cout << "changde" << changed << '\n';
        }
        int32_t val1 = Constant_fold(context, program->branches.at(0),changed);
        int32_t val2 = Constant_fold(context, program->branches.at(1),changed);
    }else if(program->type=="LessThan"){
        int32_t val1 = Constant_fold(context, program->branches.at(0),changed);
        int32_t val2 = Constant_fold(context, program->branches.at(1),changed);
    }else if(program->type=="While"){
        int32_t val1 = Constant_fold(context, program->branches.at(0),changed);
        while(val1 != 0){
            val1 = Constant_fold(context, program->branches.at(1),changed);
        }
    }else if(program->type=="If"){
        int32_t val1 = Constant_fold(context, program->branches.at(0),changed);
        int32_t val2 = Constant_fold(context, program->branches.at(1),changed);
        int32_t val3 = Constant_fold(context, program->branches.at(2),changed);
    }
    // TODO: Handle other constructs
    else{
        throw std::runtime_error("Unknown construct '"+program->type+"'");
    }
}
