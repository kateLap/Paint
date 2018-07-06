#pragma once
#include <exception>
#include"String.h"
#include<iostream>
#include<Windows.h>

using namespace std;

class InputException : public exception
{
private:
	int number;
	String message;
public:
	InputException(int _number, String str);
	~InputException();
	void Input(HWND hWnd);
};