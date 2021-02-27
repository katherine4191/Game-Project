#pragma once
class CCore
{
	SINGLETONE(CCore)

private:
	HDC		m_hdc; // 윈도우 창에 render시 꼭 필요한 것이 HDC
	HDC		m_memDC; // 더블 버퍼링 

private:
	int update();
	void render();

public:
	void init();
	int progress();

public:
	HDC GetDC() { return m_hdc; }

private:
	CCore();
	~CCore();
};