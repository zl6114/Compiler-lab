#include <iostream>
#include <iterator>
#include <string>
#include <regex>

int main(int argc, char *argv[])
{
	std::cout << argv[1] << std::endl;
	std::basic_regex<char> r(argv[1]);
	std::string regex_for_slash = "[//]"; //"\\/[[:digit:]]"
	std::basic_regex<char> replacement(regex_for_slash);
	std::cout << '\n' << std::regex_replace(argv[2],replacement,"$") << '\n';
	std::string a = std::regex_replace(argv[2],replacement,"$");
	std::string tmp;
	while( std::getline(std::cin, tmp) ){
		std::cout  << std::regex_replace(tmp, r, a) << '\n';
   	// do something with line tmp
	}
    return 0;
}



