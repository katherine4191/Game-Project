#pragma once
class CBorder
{
private:
	tPoint	m_ptPos;
	tPoint	m_ptSize;
	int		m_iPenWidth;
	UINT	m_iColor;

public:
	int update();
	void render(HDC _dc);
	void CircleRender(HDC _dc);

public:
	void SetPos(tPoint _ptPos) { m_ptPos = _ptPos; }
	void SetSize(tPoint _ptSize) { m_ptSize = _ptSize; }
	void SetPenWidth(int _iWid) { m_iPenWidth = _iWid; }
	void SetColor(UINT _iCol) { m_iColor = _iCol; }
};

