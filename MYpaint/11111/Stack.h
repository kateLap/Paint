#pragma once

//template <typename T>
//class Stack
//{
//private:
//	T *stackPtr;                      // Указатель на стек
//	int size;                         // Количество элементов в стеке
//	int top;                          // Номер текущего элемента стека
//public:
//	Stack(int = 9);                   // по умолчанию размер стека равен 9 элементам
//	Stack(const Stack<T> &);          // конструктор копирования
//	~Stack();                         // деструктор
//
//	inline void push(const T &);      // поместить элемент в вершину стека
//	inline T pop();                   // удалить элемент из вершины стека и вернуть его
//	inline const T &Peek(int) const;  // n-й элемент от вершины стека
//	inline int getStackSize() const;  // получить размер стека
//	inline T *getPtr() const;         // получить указатель на стек
//	inline int getTop() const;        // получить номер текущего элемента в стеке
//};
//
//// конструктор Стека
//template <typename T>
//Stack<T>::Stack(int maxSize) :size(maxSize) // инициализация константы
//{
//	stackPtr = new T[size]; // выделить память под стек
//	top = 0; // инициализируем текущий элемент нулем;
//}
//
//// конструктор копирования
//template <typename T>
//Stack<T>::Stack(const Stack<T> & otherStack) : size(otherStack.getStackSize()) // инициализация константы
//{
//	stackPtr = new T[size]; // выделить память под новый стек
//	top = otherStack.getTop();
//
//	for (int ix = 0; ix < top; ix++)
//		stackPtr[ix] = otherStack.getPtr()[ix];
//}
//
//// функция деструктора Стека
//template <typename T>
//Stack<T>::~Stack()
//{
//	delete[] stackPtr; // удаляем стек
//}
//
//// функция добавления элемента в стек
//template <typename T>
//inline void Stack<T>::push(const T &value)
//{
//	stackPtr[top++] = value; // помещаем элемент в стек
//}
//
//// функция удаления элемента из стека
//template <typename T>
//inline T Stack<T>::pop()
//{
//	stackPtr[--top]; // удаляем элемент из стека
//}
//
//// функция возвращает n-й элемент от вершины стека
//template <class T>
//inline const T &Stack<T>::Peek(int nom) const
//{
//	return stackPtr[top - nom - 1]; // вернуть n-й элемент стека
//}
//
//// вернуть размер стека
//template <typename T>
//inline int Stack<T>::getStackSize() const
//{
//	return size;
//}
//
//// вернуть указатель на стек (для конструктора копирования)
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