#include "Rectangles.h"

Rectangles::Rectangles()
{

}

bool Rectangles::ClickMouse(int m_x, int m_y, HDC hdc)
{
	return TwoPointsShapes::ClickMouse(m_x, m_y, hdc);
}

void Rectangles::Draw(HDC hdc, Painting* painting)
{
	HPEN p1 = CreatePen(PS_SOLID, painting->GetSize(), painting->GetPencil());
	HBRUSH b1 = CreateSolidBrush(painting->GetBrush());

	SelectObject(hdc, p1);
	SelectObject(hdc, b1);

	Rectangle(hdc, x0, y0, x1, y1);

	DeleteObject(p1);
	DeleteObject(b1);
}
