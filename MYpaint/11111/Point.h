#pragma once
#include<iostream>
#include "stdafx.h"
#include <Windowsx.h>
#include <math.h>
#include "Shape.h"

class Point : public Shape
{
private:
	int x;
	int y;

public:
	Point();
	~Point()
	{
	};
	bool ClickMouse(int m_x, int m_y, HDC hdc);
	void Draw(HDC hdc, Painting* painting);
};
