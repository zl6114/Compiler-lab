#include "ast.hpp"

#include <regex>

void propagation(
    InterpretContext &context, // Contains the parameters and variable bindings
    TreePtr program,
    bool &changed,
    int i);

int32_t Constant_propagation(
    InterpretContext &context, // Contains the parameters and variable bindings
    TreePtr program,
    bool &changed
){
    std::regex reNum("^-?[0-9]+$");
    std::regex reId("^[a-z][a-z0-9]*$");

    if( regex_match(program->type, reNum) ){
        return std::atol(program->type.c_str());
    // TODO : Check for things matching reId
    }else if( regex_match(program->type, reId) ){
        if((context.bindings[program->type] != NULL) && (changed == false)){
            int32_t val = context.bindings[program->type];
            std::string s = std::to_string(context.bindings[program->type]);
            program->type = s;
            changed = true;
            //exit(0);
        }
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
        int32_t val=Constant_propagation(context, program->branches.at(0),changed);
        std::cout<<val<<std::endl;
        return val;
    }else if(program->type=="Seq"){
        int32_t val;
        for(unsigned i=0; i<program->branches.size(); i++){
            val = Constant_propagation(context, program->branches[i],changed);
        }
        return val;
    }else if(program->type=="Assign"){
        int32_t val=Constant_propagation(context, program->branches.at(0),changed);
        context.bindings[program->value] = val;
        return val;
    }else if(program->type=="Add"){
        int32_t val1 = Constant_propagation(context, program->branches.at(0),changed);
        int32_t val2 = Constant_propagation(context, program->branches.at(1),changed);
        return val1 + val2;
    }else if(program->type=="Sub"){
        int32_t val1 = Constant_propagation(context, program->branches.at(0),changed);
        int32_t val2 = Constant_propagation(context, program->branches.at(1),changed);
        return val1 - val2;
    }else if(program->type=="LessThan"){
        int32_t val1 = Constant_propagation(context, program->branches.at(0),changed);
        int32_t val2 = Constant_propagation(context, program->branches.at(1),changed);
        if(val1 >= val2){
            return false;
        }else{
            return true;
        }
    }else if(program->type=="While"){
        int32_t val1 = Constant_propagation(context, program->branches.at(0),changed);
        while(val1 != 0){
            val1 = Constant_propagation(context, program->branches.at(1),changed);
        }
        return 0;
    }else if(program->type=="If"){
        int32_t val1 = Constant_propagation(context, program->branches.at(0),changed);
        if(val1 != 0){
            int32_t val2 = Constant_propagation(context, program->branches.at(1),changed);
            return val2;
        }else{
            int32_t val3 = Constant_propagation(context, program->branches.at(2),changed);
            return val3;
        }
    }
    // TODO: Handle other constructs
    else{
        throw std::runtime_error("Unknown construct '"+program->type+"'");
    }
}

void propagation(
    InterpretContext &context, // Contains the parameters and variable bindings
    TreePtr program,
    bool &changed,
    int i)
    {
    std::regex reId("^[a-z][a-z0-9]*$");
    if( regex_match( (program->branches[i])->type, reId ) ){
        if(context.bindings[program->branches[i]->type] != NULL){
            std::string s = std::to_string(context.bindings[program->branches[i]->type]);
            program->branches[i]->type = s;
            changed = true;
        }
    }
}
