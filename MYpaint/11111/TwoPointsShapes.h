#pragma once
#include<iostream>
#include "stdafx.h"
#include <Windowsx.h>
#include "Shape.h"


class TwoPointsShapes : public Shape
{
protected:
	int x0;
	int y0;
	int x1;
	int y1;
	bool status;

public:
	TwoPointsShapes();
	~TwoPointsShapes()
	{
	};
	bool ClickMouse(int m_x, int m_y, HDC hdc);
	void Draw(HDC hdc, Painting* painting) = 0;
};
