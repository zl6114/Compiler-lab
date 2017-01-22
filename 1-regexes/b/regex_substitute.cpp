#include <iostream>
#include <iterator>
#include <string>
#include <regex>

int main(int argc, char *argv[])
{
	std::basic_regex<char> regex_value;
	std::string regex_value_tmp;
	std::cin >> regex_value_tmp;
	regex_value = regex_value_tmp;
    // TODO: read the regex
    std::string ss;
    std::cin >> ss;
	std::string group1 = "/1";
    // TODO: read the substitution string
    std::string tmp;
    while( std::getline(std::cin, tmp) ){
		if(ss.find(group1) == true){
		ss.replace(tmp);
	    }
		ss = regex_match.str();
		std::cout << '\n' << std::regex_replace(tmp, regex_value, ss) << '\n';
   	// do something with line tmp
    }
    // TODO: for each input line
    //   TODO: Apply the regex
    //   TODO: print the new line out
    
    return 0;
}



