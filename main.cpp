#include "Hoffman_algorithm.h"

int main()
{
	Hoffman obj("my_file.txt");
	obj.analyze();
	obj.get_compressed_filename();
	obj.binary_to_text("compressed_my_file.txt");
}