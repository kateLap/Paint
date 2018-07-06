#include"MyException.h"

InputException::InputException(int _number, String str)
{
	this->number = _number;
	this->message = str;
}

void InputException::Input(HWND hWnd)
{
	MessageBox(hWnd, message.GetString(), "Ошибка", 0);
}

InputException::~InputException()
{
}