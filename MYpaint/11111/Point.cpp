#include "Point.h"

Point::Point()
{
}

bool Point::ClickMouse(int m_x, int m_y, HDC hdc)
{
	x = m_x;
	y = m_y;	
	return 0;
}

void Point::Draw(HDC hdc, Painting* painting)
{
	int R = painting->GetSize();

	HPEN p1 = CreatePen(PS_SOLID, painting->GetSize(), painting->GetPencil());
	HBRUSH b1 = CreateSolidBrush(painting->GetPencil());

	SelectObject(hdc, p1);
	SelectObject(hdc, b1);

	Ellipse(hdc, x - R, y + R, x + R, y - R);

	DeleteObject(p1);
	DeleteObject(b1);
}