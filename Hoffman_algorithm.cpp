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

		std::vector<std::pair<char, int>> vec(m_map.size());

		for (const auto& var : m_map)
		{
			multi.insert({ var.second, var.first });
		}
		make_symbols_tree(multi);
		tree_to_table("", root);
		for (const auto& var : char_table)
		{
			std::cout << "symbol = " << var.first << " code = " << var.second << std::endl;
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
	if(file) {

		std::string code;
		char ch;
		std::ofstream compressed_file("compressed_" + filename);
		for (decltype(auto) var : char_table)
		{
			compressed_file << var.first << " " << var.second << '\n';
		}

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

void Hoffman::make_symbols_tree(std::multimap<int, char>& multi)
{
	std::priority_queue<Node*,std::vector<Node*>, Node::MyCompare> p_queue;
	for (multimap<int, char>::iterator i = multi.begin(); i != multi.end(); i++)
	{
		std::cout << i->first << " " << i->second << std::endl;
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
