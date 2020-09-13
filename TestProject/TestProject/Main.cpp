#include <iostream>
#include <vector>
#include "TestLib.h"

int main() {

	std::cout << "Hello, World\n";
	std::vector<int> array;

	array.emplace_back( 10 );
	array.emplace_back( 15 );
	array.emplace_back( 16 );

	for( auto& i : array ) {
		std::cout << i << std::endl;
		/*int *i = (int*)0x1234567879;
		*i = 10;*/
	}

	Test();

	return 0;
}