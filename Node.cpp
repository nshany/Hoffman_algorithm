#include "Node.h"
#include <iostream>

Node::Node() : left(nullptr), right(nullptr) {}
Node::Node(int count, char symbol) :m_count(count), m_symbol(symbol), left(nullptr), right(nullptr) {}
Node::Node(Node* L, Node* R) :left(L), right(R), m_count(L->m_count + R->m_count) {}