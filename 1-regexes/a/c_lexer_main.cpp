#include "histogram.hpp"
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iomanip>


// Define the instance of the variable that is declared in the header
TokenValue yylval;
int main()
{
    while(1){
        TokenType type=(TokenType)yylex();
        std::cout << "\"Class\": "; 
        if(type==None){
            break; // No more tokens
        }else if(type==Keyword){
        }else if(type==Identifier){
            std::cout << "\"Identifier\"  \"Text\": " << *yylval.wordValue << std::endl; 
        }else if(type==Operator){
        }else if(type==Constant){
        }else if(type==StringLiteral){
        }else if(type==Invalid){ 
        }else{
            assert(0); // There are only three token types.
            return 1;
        }
    }
    return 0;
}
