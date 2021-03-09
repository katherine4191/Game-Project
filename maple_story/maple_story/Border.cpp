#include "pch.h"
#include "Border.h"

int CBorder::update()
{
	return 0;
}

void CBorder::render(HDC _dc)
{
	HPEN hPen = CreatePen(PS_SOLID, m_iPenWidth, m_iColor);
	HPEN hOldPen = (HPEN)SelectObject(_dc, hPen);

	MoveToEx(_dc, m_ptPos.fX - (m_ptSize.fX / 2.f), m_ptPos.fY - (m_ptSize.fY / 2.f), NULL);
	LineTo(_dc, m_ptPos.fX + (m_ptSize.fX / 2.f), m_ptPos.fY - (m_ptSize.fY / 2.f));
	LineTo(_dc, m_ptPos.fX + (m_ptSize.fX / 2.f), m_ptPos.fY + (m_ptSize.fY / 2.f));
	LineTo(_dc, m_ptPos.fX - (m_ptSize.fX / 2.f), m_ptPos.fY + (m_ptSize.fY / 2.f));
	LineTo(_dc, m_ptPos.fX - (m_ptSize.fX / 2.f), m_ptPos.fY - (m_ptSize.fY / 2.f));

	SelectObject(_dc, hOldPen);
	DeleteObject(hPen);
}

void CBorder::CircleRender(HDC _dc)
{
	HPEN hPen = CreatePen(PS_SOLID, m_iPenWidth, m_iColor);
	HPEN hOldPen = (HPEN)SelectObject(_dc, hPen);
	HGDIOBJ temp = GetStockObject(HOLLOW_BRUSH);
	HGDIOBJ oldTemp = (HGDIOBJ)SelectObject(_dc, temp);
	Ellipse(_dc, m_ptPos.fX - (m_ptSize.fX / 2.f), m_ptPos.fY - (m_ptSize.fY / 2.f), m_ptPos.fX + (m_ptSize.fX / 2.f), m_ptPos.fY + (m_ptSize.fY / 2.f));
	SelectObject(_dc, oldTemp);
	SelectObject(_dc, hOldPen);
	DeleteObject(hPen);
	DeleteObject(temp);
}
