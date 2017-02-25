#include "ast.hpp"

#include <regex>

int32_t Dead_branches_removal(
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
        int32_t val=Dead_branches_removal(context, program->branches.at(0),changed);
        std::cout<<val<<std::endl;
        return val;
    }else if(program->type=="Seq"){
        int32_t val;
        for(unsigned i=0; i<program->branches.size(); i++){
            val = Dead_branches_removal(context, program->branches[i],changed);
        }
        return val;
    }else if(program->type=="Assign"){
        int32_t val=Dead_branches_removal(context, program->branches.at(0),changed);
        context.bindings[program->value] = val;
        return val;
    }else if(program->type=="Add"){
        int32_t val1 = Dead_branches_removal(context, program->branches.at(0),changed);
        int32_t val2 = Dead_branches_removal(context, program->branches.at(1),changed);
        return val1 + val2;
    }else if(program->type=="Sub"){
        int32_t val1 = Dead_branches_removal(context, program->branches.at(0),changed);
        int32_t val2 = Dead_branches_removal(context, program->branches.at(1),changed);
        return val1 - val2;
    }else if(program->type=="LessThan"){
        int32_t val1 = Dead_branches_removal(context, program->branches.at(0),changed);
        int32_t val2 = Dead_branches_removal(context, program->branches.at(1),changed);
        if(val1 >= val2){
            return false;
        }else{
            return true;
        }
    }else if(program->type=="While"){
        int32_t val1 = Dead_branches_removal(context, program->branches.at(0),changed);
        while(val1 != 0){
            val1 = Dead_branches_removal(context, program->branches.at(1),changed);
        }
        return 0;
    }else if(program->type=="If"){
        if( regex_match( (program->branches.at(0))->type, reNum ) ){
            changed = true;
            if((program->branches.at(0))->type == "0"){
                program->type = program->branches[2]->type;
                program->value = program->branches[2]->value;
                program->branches = program->branches[2]->branches;
                return 0;
            }else{
                program->type = program->branches[1]->type;
                program->value = program->branches[1]->value;
                program->branches = program->branches[1]->branches;
                return 0;
            }
        }
        int32_t val1 = Dead_branches_removal(context, program->branches.at(0),changed);
        if(val1 != 0){
            int32_t val2 = Dead_branches_removal(context, program->branches.at(1),changed);
            return val2;
        }else{
            int32_t val3 = Dead_branches_removal(context, program->branches.at(2),changed);
            return val3;
        }
    }
    // TODO: Handle other constructs
    else{
        throw std::runtime_error("Unknown construct '"+program->type+"'");
    }
}
