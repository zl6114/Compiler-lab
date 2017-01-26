#include <iostream>
#include <iterator>
#include <string>
#include <regex>

int main(int argc, char *argv[])
{
	//std::cout << argv[1] << std::endl; //testing first input
	std::basic_regex<char> r(argv[1]);
	std::string a = argv[2];
	//std::cout << a << std::endl; //testing a
	std::string tmp;
	while( std::getline(std::cin, tmp) ){
		std::cout  << std::regex_replace(tmp, r, a,std::regex_constants::format_sed) << '\n';
   	// do something with line tmp
	}
    return 0;
}



