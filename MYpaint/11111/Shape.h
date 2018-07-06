#pragma once
#include "stdafx.h"
#include <Windowsx.h>
#include<iostream>
#include "Painting.h"

using namespace std;

class Shape
{
public:
	Shape()
	{
	};
	virtual ~Shape()
	{
	}

	virtual bool ClickMouse(int m_x, int m_y, HDC hdc) = 0;
	virtual void Draw(HDC hdc, Painting* painting) = 0;
};