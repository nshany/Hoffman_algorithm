#include <iostream>
#include "Hoffman_algorithm.h"
#include <fstream>
int main()
{
	std::cout << "Input the file name   ";

	char ch;
	std::string filename = "";
	while (std::cin.get(ch) && ch != '\n')
		filename += ch;
	std::fstream my_file;


	Hoffman obj("sample-2mb-text-file.txt");
	obj.analyze();
	std::cout<<obj.get_compressed_filename();
}