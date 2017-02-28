#include "ast.hpp"
#include <algorithm>
#include <string>
#include <regex>
#include <sstream>
#include <fstream>
#include <vector>
#include <sstream>

static int makeNameUnq=0;

static std::string makeName(std::string base)
{
    return base+std::to_string(makeNameUnq++);
}

void CompileRec(
    std::ofstream &src1,    // The name of the register to put the result in
    TreePtr program,
    std::vector<std::string>& v
){
    std::regex reNum("^-?[0-9]+$");
    std::regex reId("^[a-z][a-z0-9]*$");

    if( regex_match( program->type, reNum ) ){
        src1 << program->type;
    }else if( regex_match( program->type, reId ) ){
        src1 << program->type << ";\n";

    }else if(program->type=="Param"){
    }else if(program->type=="Seq"){
        int size = program->branches.size() - 1;
        for(unsigned i=0; i<program->branches.size(); i++){
            CompileRec(src1, program->branches[i],v);
        }
        if( regex_match( program->branches[size]->type, reId ) ){
            src1 << "std::cout << " << program->branches[size]->type << " << std::endl;\n";
        }
    }else if(program->type=="Input"){
        src1 << "int " << "___cin" << ";\n";
        src1 << "std::cin >> ___cin";
    }else if(program->type=="Output"){
        src1 << "std::cout << ";
        CompileRec(src1, program->branches.at(0),v);
        src1 << " << std::endl;\n";
    }else if(program->type=="Assign"){
        if( regex_match( program->value, reId ) ){
            auto it = std::find(v.begin(), v.end(), program->value);
             if (it != v.end())
             {     // Found
             }else
             {
                 v.push_back(program->value);
                 src1 << "int " << program->value << ";\n"; // Not Found
             }
        }
        src1 << program->value;
        src1 << " = ";
        CompileRec(src1, program->branches.at(0),v);
        src1 << ";\n";
    }else if(program->type=="Add"){
        CompileRec(src1, program->branches.at(0),v);
        src1 << " + ";
        CompileRec(src1, program->branches.at(1),v);
    }else if(program->type=="Sub"){
        CompileRec(src1, program->branches.at(0),v);
        src1 << " - ";
        CompileRec(src1, program->branches.at(1),v);
    }else if(program->type=="LessThan"){
        CompileRec(src1, program->branches.at(0),v);
        src1 << " < ";
        CompileRec(src1, program->branches.at(1),v);

    }else if(program->type == "While"){
        src1 << "while";
        src1 << " ( ";
        CompileRec(src1, program->branches.at(0),v);
        src1 << " )\n";
        src1 << " {\n";
        CompileRec(src1, program->branches.at(1),v);
        src1 << " }\n";
    }else if(program->type=="If"){
        src1 << "if";
        src1 << " ( ";
        CompileRec(src1, program->branches.at(0),v);
        src1 << " )\n{ ";
        CompileRec(src1, program->branches.at(1),v);
        src1 << "}else{\n";
        CompileRec(src1, program->branches.at(2),v);
        src1 << "}\n";
    }
    // TODO : handle the others
    else{
        throw std::runtime_error("Unknown construct '"+program->type+"'");
    }
}

void MipsGen(
    TreePtr program,
    std::ofstream &src1,
    std::vector<std::string>& v
){
    // Create a register to hold the final result

    // Compile the whole thing
    CompileRec(src1, program,v);

    // Put the result out
}


int main(int argc, char *argv[])
{
    std::vector<std::string> v;
    std::stringstream temp;
    std::string tempstring;
    std::ifstream src(argv[1]);
    temp << argv[2] <<".cpp";
    tempstring = temp.str();
    std::ofstream src1(tempstring);
    std::ofstream src2("code_gen_script.sh");
    if(!src.is_open()){
        fprintf(stderr, "Couldn't open '%s'\n", argv[1]);
        exit(1);
    }

    if(!src1.is_open()){
        fprintf(stderr, "Couldn't open '%s'\n", argv[2]);
        exit(1);
    }
    src1<< "#include <iostream>\n";
    src1 << "int main(){\n";
    TreePtr tree=Parse(src);

    MipsGen(tree,src1,v);
    src1 << "return 0; \n}\n";
    //src1 << "Writing this to a file.\n";
    src1.close();

    src2 << "chmod u+x ./code_gen_script.sh\n";
    src2 << "mips-linux-gnu-g++ -static "<< tempstring << " -o " << argv[2]<< "\n";
    src2 << "qemu-mips " << argv[2] << "\n";

    src2.close();

    system("./code_gen_script.sh");

    return 0;
}
