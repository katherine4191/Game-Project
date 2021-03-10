#include "pch.h"
#include "UI.h"

#include "KeyMgr.h"

CUI::CUI()
	: m_ptUISize(POINT{ 0, 0 })
{
}

CUI::~CUI()
{
}

int CUI::update()
{
	MouseCheck();

	list<CUI*>::iterator iter = m_listChild.begin();
	for (; iter != m_listChild.end(); ++iter)
	{
		(*iter)->update();
	}

	return 0;
}

void CUI::render(HDC _dc)
{
	list<CUI*>::iterator iter = m_listChild.begin();
	for (; iter != m_listChild.end(); ++iter)
	{
		(*iter)->render(_dc);
	}
}

void CUI::OnMouseFirst()
{
}

void CUI::OnMouse()
{
}

void CUI::OnMouseLBtnDown()
{
}

void CUI::OnMouseLBtnUp()
{
}

void CUI::OnMouseOut()
{
}

void CUI::MouseCheck()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if (m_ptPos.fX <= ptMouse.x && ptMouse.x <= m_ptPos.fX + m_ptUISize.x
		&& m_ptPos.fY <= ptMouse.y && ptMouse.y <= m_ptPos.fY + m_ptUISize.y)
	{
		m_tState.bMouseOn = true;
		// 마우스가 UI 범위에 들어와 있을 때
		if (GET_KEY(VK_LBUTTON, KEY_STATE::PRESS))
		{
			m_tState.bLBtnClicked = true;
		}
		else if (GET_KEY(VK_LBUTTON, KEY_STATE::HOLD) && m_tState.bLBtnClicked)
		{
			m_tState.bLBtnClicked = true;
		}
		else
			m_tState.bLBtnClicked = false;
	}
	else
	{
		m_tState.bMouseOn = false;

		if (GET_KEY(VK_LBUTTON, KEY_STATE::AWAY))
			m_tState.bLBtnClicked = false;
	}
}