#ifndef _HOFFMAN_H_
#define _HOFFMAN_H_
#include <vector>
#include <string>
#include <map>
#include "Node.h"

class Hoffman {
public:
	Hoffman(std::string text);

	void analyze();
	std::string get_compressed_filename() const;
	void binary_to_text(std::string filename);
private:
	std::string decode_symbol(int ch);
	void make_symbols_tree(std::multimap<int, char> &);
	void tree_to_table(std::string code, Node* node);

	std::map<char, std::string> char_table;
	Node* root;
	std::string filename;
	std::string m_result;
};

#endif