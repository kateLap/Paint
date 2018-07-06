#include<iostream>
using namespace std;

#include"String.h"

String::String(int len)
{
	this->size = len;
	this->string_my = new char[this->size + 1];
	strcpy_s(this->string_my, 1, "");
}

String::String(const String & temp)
{
	this->size = temp.size;
	this->string_my = new char[this->size + 1];
	strcpy_s(this->string_my, strlen(temp.string_my) + 1, temp.string_my);
}

String& String::operator = (const String & temp)
{
	if (this == &temp)
	{
		return *this;
	}

	if (this->string_my != nullptr)
	{
		delete[] this->string_my;
	}

	this->size = temp.size;
	this->string_my = new char[this->size + 1];
	strcpy_s(this->string_my, strlen(temp.string_my) + 1, temp.string_my);
	return *this;
}