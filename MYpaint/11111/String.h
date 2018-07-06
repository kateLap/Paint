#pragma once
using namespace std;
#include<iostream>

class String
{
private:
	char* string_my;
	int size;

public:
	String(const String & temp);//
	explicit String(char* str)
	{
		this->size = (int)strlen(str);
		this->string_my = new char[this->size + 1];
		strcpy_s(this->string_my, this->size + 1, str);
	}
	explicit String(int len = 80);

	~String()
	{
		delete[] this->string_my;
	}

	char* String::GetString()
	{
		return string_my;
	}

	String& operator = (const String & temp);
};