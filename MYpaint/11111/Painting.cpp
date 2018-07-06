#include "Painting.h"

Painting::Painting()
{
	pencil_color = colors[0];
	brush_color = colors[1];
	pencil_size = 2;
}
void Painting::Set(COLORREF _pencil_color, COLORREF _brush_color,  int _pencil_size)
{
	pencil_color = _pencil_color;
	brush_color = _brush_color;
	pencil_size = _pencil_size;
}

COLORREF Painting::GetPencil()
{
	return pencil_color;
}

COLORREF Painting::GetBrush()
{
	return brush_color;
}

int Painting::GetSize()
{
	return pencil_size;
}