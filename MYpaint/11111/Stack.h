#pragma once

//template <typename T>
//class Stack
//{
//private:
//	T *stackPtr;                      // ��������� �� ����
//	int size;                         // ���������� ��������� � �����
//	int top;                          // ����� �������� �������� �����
//public:
//	Stack(int = 9);                   // �� ��������� ������ ����� ����� 9 ���������
//	Stack(const Stack<T> &);          // ����������� �����������
//	~Stack();                         // ����������
//
//	inline void push(const T &);      // ��������� ������� � ������� �����
//	inline T pop();                   // ������� ������� �� ������� ����� � ������� ���
//	inline const T &Peek(int) const;  // n-� ������� �� ������� �����
//	inline int getStackSize() const;  // �������� ������ �����
//	inline T *getPtr() const;         // �������� ��������� �� ����
//	inline int getTop() const;        // �������� ����� �������� �������� � �����
//};
//
//// ����������� �����
//template <typename T>
//Stack<T>::Stack(int maxSize) :size(maxSize) // ������������� ���������
//{
//	stackPtr = new T[size]; // �������� ������ ��� ����
//	top = 0; // �������������� ������� ������� �����;
//}
//
//// ����������� �����������
//template <typename T>
//Stack<T>::Stack(const Stack<T> & otherStack) : size(otherStack.getStackSize()) // ������������� ���������
//{
//	stackPtr = new T[size]; // �������� ������ ��� ����� ����
//	top = otherStack.getTop();
//
//	for (int ix = 0; ix < top; ix++)
//		stackPtr[ix] = otherStack.getPtr()[ix];
//}
//
//// ������� ����������� �����
//template <typename T>
//Stack<T>::~Stack()
//{
//	delete[] stackPtr; // ������� ����
//}
//
//// ������� ���������� �������� � ����
//template <typename T>
//inline void Stack<T>::push(const T &value)
//{
//	stackPtr[top++] = value; // �������� ������� � ����
//}
//
//// ������� �������� �������� �� �����
//template <typename T>
//inline T Stack<T>::pop()
//{
//	stackPtr[--top]; // ������� ������� �� �����
//}
//
//// ������� ���������� n-� ������� �� ������� �����
//template <class T>
//inline const T &Stack<T>::Peek(int nom) const
//{
//	return stackPtr[top - nom - 1]; // ������� n-� ������� �����
//}
//
//// ������� ������ �����
//template <typename T>
//inline int Stack<T>::getStackSize() const
//{
//	return size;
//}
//
//// ������� ��������� �� ���� (��� ������������ �����������)
//template <typename T>
//inline T *Stack<T>::getPtr() const
//{
//	return stackPtr;
//}
//
//template <typename T>
//inline int Stack<T>::getTop() const
//{
//	return top;
//}

using namespace std;

template <typename T> class Stack;
#include "Node.h"

template <typename T>
class Stack
{
	Node<T> *head;

	void Add(Node<T>*& head, T  element)
	{
		if (head == NULL)
		{
			head = new Node<T>(element);
		}
		else
		{
			Node<T>* temp = new Node<T>(element);
			temp->next = head;
			head = temp;
		}
	}

	void DeleteStack(Node<T>*& head)
	{
		while (head != NULL)
		{
			Node<T>* temp = head->next;
			delete head;
			head = temp;
		}
	}

	T Peek(Node<T>* head, int number)
	{
		if (head == NULL)
		{
			return NULL;
		}

		Node<T>* temp = head;

		while (number > 0)
		{
			temp = temp -> next;
			number--;
		}
		return temp->item;
	}

	void DeleteNode(Node<T>*& head, T  element)
	{
		if (head == NULL)
		{
			return;
		}
		Node<T>* temp = head;
		Node<T>* mem;

		while (temp->item != element)
		{
			mem = temp;
			temp = temp->next;
		}

		Node<T>* node_del = temp;
		mem->next = temp->next;
		delete node_del;
	}

	void FindNode(Node<T>*& head, T element)
	{
		if (head == NULL)
		{
			return NULL;
		}
		Node<T>* temp = head;
		while (temp->item != element)
		{
			if (temp->next == NULL)
			{
				return NULL;
			}
			temp = temp->next;
		}
		return temp;
	}

public:
	Stack() 
	{
		head = NULL;
	}

	~Stack() 
	{
		DeleteStack(head);
	}

	void Add(T element)
	{
		Add(head, element);
	}

	void DeleteNode(T  element)
	{
		DeleteNode(head, element);
	}

	void FindNode(T element)
	{
		FindNode(head, element);
	}

	T Peek(int number)
	{
		return Peek(head, number);
	}

	Node<T>* Begin()
	{
		return head;
	}

	Node<T>* End()
	{
		Node<T>* temp = head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		return temp;
	}

	class Iterator
	{
		Node<T>* pointer;

	public:

		Iterator()
		{
			pointer = NULL;
		}

		Iterator(Node<T> * temp) : pointer(temp)
		{
		}

		~Iterator()
		{
		}

		void operator++()
		{
			if (pointer->next != NULL)
			{
				pointer = pointer->next;
			}
		}

		void operator--()
		{
			Node<T>* temp = pointer;
			while (pointer->next != temp)
			{
				pointer = pointer->next;
			}
			return pointer;
		}

		T operator *()
		{
			return pointer->item;
		}
	};
};