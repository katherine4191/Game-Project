#pragma once
class CCore
{
	SINGLETONE(CCore)

private:
	HDC		m_hdc; // ������ â�� render�� �� �ʿ��� ���� HDC
	HDC		m_memDC; // ���� ���۸� 

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