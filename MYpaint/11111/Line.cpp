#include "Line.h"

Line::Line()
{
}

bool Line::ClickMouse(int m_x, int m_y, HDC hdc)
{
	return TwoPointsShapes::ClickMouse(m_x, m_y, hdc);
}

void Line::Draw(HDC hdc, Painting* painting)
{
	MoveToEx(hdc, x0, y0, NULL);

	HPEN p1 = CreatePen(PS_SOLID, painting->GetSize(), painting->GetPencil());
	SelectObject(hdc, p1);

	LineTo(hdc, x1, y1);

	DeleteObject(p1);
}
