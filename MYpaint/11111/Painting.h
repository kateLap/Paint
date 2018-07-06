#pragma once
#include<iostream>
#include "stdafx.h"
#include <Windowsx.h>

static const COLORREF BLACK_COLOR = RGB(0, 0, 0);
static const COLORREF WHITE_COLOR = RGB(255, 255, 255);
static const COLORREF RED_COLOR = RGB(255, 0, 0);
static const COLORREF GREEN_COLOR = RGB(0, 255, 0);
static const COLORREF BLUE_COLOR = RGB(0, 0, 255);
static const COLORREF CYAN_COLOR = RGB(0, 255, 255);
static const COLORREF YELLOW_COLOR = RGB(255, 255, 0);
static const COLORREF ORANGE_COLOR = RGB(255, 104, 0);
static const COLORREF PURPLE_COLOR = RGB(255, 0, 255);

static const COLORREF colors[9] = { BLACK_COLOR, WHITE_COLOR, RED_COLOR, GREEN_COLOR, BLUE_COLOR, CYAN_COLOR,
YELLOW_COLOR, ORANGE_COLOR, PURPLE_COLOR };

class Painting
{
	COLORREF pencil_color;
	COLORREF brush_color;
	int pencil_size;
public:
	Painting();
	~Painting()
	{
	};
	void Set(COLORREF _pencil_color, COLORREF _brush_color, int _pencil_size);
	int GetSize();
    COLORREF GetPencil();
	COLORREF GetBrush();
};