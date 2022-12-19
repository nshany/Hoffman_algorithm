#include <map>
#include <queue>
#include <iostream>
#include "Hoffman_algorithm.h"
#include <algorithm>
#include <fstream>
using namespace std;

Hoffman::Hoffman(string filename) : filename(filename), root(nullptr) {}

void Hoffman::analyze()
{
	map<char, int> m_map;
	char ch;
	std::multimap<int, char> multi;
	std::fstream file(filename);
	if (file) {
		file.unsetf(ios::skipws);
		while (!file.eof()) 
		{
			file >> ch;
			if (m_map.find(ch) == m_map.end())
			{
				m_map.insert(std::make_pair(ch, 1));
			}
			else
			{
				++m_map[ch];
			}
		}

		for (const auto& var : m_map)
		{
			multi.insert({ var.second, var.first });
		}

		make_symbols_tree(multi);

		tree_to_table("", root);
		for (const auto& var : char_table)
		{
			std::cout << "symbol = " << var.first << " code = " << var.second << '\n';
		}
		file.close();
	}
	else
	{
		std::cerr << "file openning failed" << '\n';
	}
}

std::string Hoffman::get_compressed_filename() const
{
	std::fstream file(filename);
	file.unsetf(ios::skipws);
	if(file) {

		std::string code;
		char ch;
		std::ofstream compressed_file("compressed_" + filename);
		for (decltype(auto) var : char_table)
		{
			compressed_file << var.first << " " << var.second << '\n';
		}

		compressed_file << '\n';

		while (!file.eof())
		{
			file >> ch;
			code = char_table.at(ch);
			compressed_file << code;
		}

		compressed_file.close();
		file.close();
		return "compressed_" + filename;
	}
	else
	{
		std::cerr << "file openning failed" << '\n';
		return "";
	}
}

void Hoffman::binary_to_text(std::string filename)
{
	std::fstream file(filename);
	std::string line;
	std::map<std::string, char> reverse_tree;
	std::ofstream decompressed_file("decompressed_" + filename);
	file.unsetf(ios::skipws);
	if (file)
	{
		char ch;
		std::string code;
		int counter = 0;
		while(std::getline(file, line))
		{
			if (line != "") {
				ch = line[0];
				code = line.substr(2, line.size() - 1);
				reverse_tree.insert({ code, ch });
			}
			else
			{
				break;
			}
		}
		
		std::string str;
		code = "";
		while (!file.eof())
		{
			file >> ch;
			code += ch;
			if (reverse_tree.find(code) != reverse_tree.end()) {
				decompressed_file << reverse_tree[code];
				code = "";
			}
		}
	}
	else {
		std::cerr << "file openning failed" << '\n';
	}
}

void Hoffman::make_symbols_tree(std::multimap<int, char>& multi)
{
	std::priority_queue<Node*,std::vector<Node*>, Node::MyCompare> p_queue;
	for (multimap<int, char>::iterator i = multi.begin(); i != multi.end(); i++)
	{
		std::cout << i->first << " " << i->second << '\n';
		p_queue.push(new Node(i->first, i->second));
	}

	while (p_queue.size() != 0)
	{
		Node* left = nullptr, * right = nullptr;
		if (p_queue.size() != 1)
		{
			left = p_queue.top();
			p_queue.pop();
		}
		else
		{
			root = p_queue.top();
			p_queue.pop();
			break;
		}

		right = p_queue.top();
		if (p_queue.size() != 1)
		{
			p_queue.pop();
			p_queue.push(new Node(left, right));
		}
		else
		{
			root = new Node(left, right);
			break;
		}
	}
}

void Hoffman::tree_to_table(std::string code, Node *tmp)
{
	if (tmp->left == nullptr && tmp->right == nullptr)
	{
		char_table.insert({ tmp->m_symbol, code });
		code = code.substr(0, code.size() - 1);
		return;
	}

	tree_to_table(code + '0',tmp->left);
	tree_to_table(code + '1', tmp->right);
}
