#pragma once
#include<iostream>
#include "stdafx.h"
#include "TwoPointsShapes.h"
#include <Windowsx.h>

class Line: public TwoPointsShapes
{
public:
	Line();
	~Line()
	{
	};
	bool ClickMouse(int m_x, int m_y, HDC hdc);
	void Draw(HDC hdc, Painting* painting);
};