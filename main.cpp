#include <iostream>
#include "Hoffman_algorithm.h"
#include <fstream>
int main()
{
	/*std::cout << "Input the file name   ";

	char ch;
	std::string filename = "";
	while (std::cin.get(ch) && ch != '\n')
		filename += ch;
	std::fstream my_file;*/


	Hoffman obj("my_file.txt");
	//obj.analyze();
	//obj.get_compressed_filename();
	obj.binary_to_text("compressed_my_file.txt");
}