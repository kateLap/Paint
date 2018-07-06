#include "TwoPointsShapes.h"

TwoPointsShapes::TwoPointsShapes()
{
	this->status = 0;
}

bool TwoPointsShapes::ClickMouse(int m_x, int m_y, HDC hdc)
{
	switch (status)
	{
		case 0:
		{
			x0 = m_x;
			y0 = m_y;
			status = 1;
			break;
		}
		case 1:
		{
			x1 = m_x;
			y1 = m_y;
			status = 0;
			break;
		}
	}
	return status;
}
