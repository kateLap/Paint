#pragma once

template <typename T>
class Node
{
	friend class Stack<T>;

public:	
	Node()
	{
	}
	Node(T &_item)
	{
		item = _item;
		next = NULL;
	}

private:
	T item;
	Node<T>* next;
};