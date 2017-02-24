#include "ast.hpp"

#include <regex>

int32_t Interpret(
    InterpretContext &context, // Contains the parameters and variable bindings
    TreePtr program
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
        int32_t val=Interpret(context, program->branches.at(0));
        std::cout<<val<<std::endl;
        return val;
    }else if(program->type=="Seq"){
        int32_t val;
        for(unsigned i=0; i<program->branches.size(); i++){
            val = Interpret(context, program->branches[i]);
        }
        return val;
    }else if(program->type=="Assign"){
        int32_t val=Interpret(context, program->branches.at(0));
        context.bindings[program->value] = val;
        return val;
    }else if(program->type=="Add"){
        int32_t val1 = Interpret(context, program->branches.at(0));
        int32_t val2 = Interpret(context, program->branches.at(1));
        if((regex_match((program->branches.at(0))->type,reNum))
        &&((program->branches.at(0))->type,reNum))){
            program->branches.clear();
            std::string s = std::to_string(val1+val2);
            program->type = s;
        }
        return val1 + val2;
    }else if(program->type=="Sub"){
        int32_t val1 = Interpret(context, program->branches.at(0));
        int32_t val2 = Interpret(context, program->branches.at(1));
        return val1 - val2;
    }else if(program->type=="LessThan"){
        int32_t val1 = Interpret(context, program->branches.at(0));
        int32_t val2 = Interpret(context, program->branches.at(1));
        if(val1 >= val2){
            return false;
        }else{
            return true;
        }
    }else if(program->type=="While"){
        int32_t val1 = Interpret(context, program->branches.at(0));
        while(val1 != 0){
            val1 = Interpret(context, program->branches.at(1));
        }
        return 0;
    }else if(program->type=="If"){
        int32_t val1 = Interpret(context, program->branches.at(0));
        if(val1 != 0){
            int32_t val2 = Interpret(context, program->branches.at(1));
            return val2;
        }else{
            int32_t val3 = Interpret(context, program->branches.at(2));
            return val3;
        }
    }
    // TODO: Handle other constructs
    else{
        throw std::runtime_error("Unknown construct '"+program->type+"'");
    }
}
