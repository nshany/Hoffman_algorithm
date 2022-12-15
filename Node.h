#ifndef _NODE_H_
#define _NODE_H_

class Node
{
public:
	Node();
	Node(const Node& node);
	Node(int count, char symbol);
	Node(Node* L, Node* R);

	bool CMPRoperator(const Node* left, const Node* right);

	int m_count;
	char m_symbol;
	Node* left, * right;
	
	class MyCompare {
	public:

		bool operator()(Node* left, Node* right) {
			return (left->m_count > right->m_count);
		}
	};
};
#endif