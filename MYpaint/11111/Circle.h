#pragma once
#include<iostream>
#include "stdafx.h"
#include <Windowsx.h>
#include <math.h>
#include "TwoPointsShapes.h"

class Circle: public TwoPointsShapes
{
public:
	Circle();
	~Circle()
	{
	};
	bool ClickMouse(int m_x, int m_y, HDC hdc);
	void Draw(HDC hdc, Painting* painting);
};
