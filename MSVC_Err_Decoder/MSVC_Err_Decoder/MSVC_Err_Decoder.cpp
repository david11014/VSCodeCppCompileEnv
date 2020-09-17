#include <iostream>
#include <string>
#include <map>
#include <regex>

int main() {

	std::map<int, std::string> project_map;
	std::string input;
	
	// match "(PROJECT_INDEX)>------Build started : Project: (PROJECT_NAME), Configuration : Release x64------";
	std::regex reg_StartBuild("(\\d+)>\\-\\-\\-\\-\\-\\-.+Project: (.+),");
	// match "(PROJECT_INDEX)>(OpenGL.cpp(720)INFO)";	
	std::regex reg_ERROR("(\\d+)>(.+\\..+\\(\\d+\\).+)");
	// match absulate path error message
	std::regex reg_ERROR_ABS("(\\d+)>([A-Za-z]:\\\\.+:.*)");
	// match link error
	// (PROJECT_INDEX)>LINK : fatal error LNK1181 : cannot open input file 'cgal.lib'
	std::regex reg_LINK("(\\d+)>LINK : (.+)");
	std::smatch match;

	while (std::getline(std::cin, input)){

		// new project build start
		if (std::regex_search(input, match, reg_StartBuild)) {
			std::cout << input << std::endl;
			if (match.size() >= 3) {
				std::cout << "Project " << match[ 2 ].str() << " index is " << match[ 1 ].str() <<std::endl;
				project_map[std::atoi(match[1].str().c_str())] = match[2].str();
			}
		}
		else if (std::regex_search(input, match, reg_ERROR_ABS)) {
			if (match.size() >= 3) {
				std::string project = project_map[std::atoi(match[1].str().c_str())];
				std::cout << match[2].str() << std::endl;
			}
		}
		// replace index to project name
		else if (std::regex_search(input, match, reg_ERROR)) {
			if (match.size() >= 3) {
				std::string project = project_map[std::atoi(match[1].str().c_str())];
				std::cout << project << "\\" << match[2].str() << std::endl;
			}
		}
		else if (std::regex_search(input, match, reg_LINK)) {
			if (match.size() >= 3) {
				std::string project = project_map[std::atoi(match[1].str().c_str())];
				std::cout << project << "\\LINK(0) : " << match[2].str() << std::endl;
			}
		}
		else {
			std::cout << input << std::endl;
		}
	}

	return 0;
}