#pragma once
#include "Obj.h"
#include "Border.h"

class CUI
	: public CObj
{
protected:
	list<CUI*>		m_listChild;
	POINT			m_ptUISize;
	tUIState		m_tState;

public:
	virtual int update();
	virtual void render(HDC _dc);

public:
	virtual void OnMouseFirst();
	virtual void OnMouse();
	virtual void OnMouseOut();
	virtual void OnMouseLBtnDown();
	virtual void OnMouseLBtnUp();


public:
	bool IsMouseOn() { return m_tState.bMouseOn; }
	bool IsLBtnClicked() { return m_tState.bLBtnClicked; }
	bool IsRBtnClicked() { return m_tState.bRBtnClicked; }

private:
	void MouseCheck();

public:
	CUI();
	virtual ~CUI();
};

