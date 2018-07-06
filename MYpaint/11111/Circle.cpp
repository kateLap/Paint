#include "Circle.h"

Circle::Circle()
{

}

bool Circle::ClickMouse(int m_x, int m_y, HDC hdc)
{
	return TwoPointsShapes::ClickMouse(m_x, m_y, hdc);
}

void Circle::Draw(HDC hdc, Painting* painting)
{
		int R = (int)sqrt((x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0));
		
		HPEN pen = CreatePen(PS_SOLID, painting->GetSize(), painting->GetPencil());
		HBRUSH brush = CreateSolidBrush(painting->GetBrush());

		SelectObject(hdc, pen);
		SelectObject(hdc, brush);

		Ellipse(hdc, x0 - R, y0 + R, x0 + R, y0 - R);

		DeleteObject(pen);
		DeleteObject(brush);
}
