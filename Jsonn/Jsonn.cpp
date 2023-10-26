#include <iostream>
#include <iomanip>
#include "Planet.hpp"

using namespace nlohmann;


int main()
{
	std::string filename;
	std::cout << "Enter a filename: "; std::cin >> filename;
	std::ifstream file(filename + ".json");


}