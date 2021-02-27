#include "pch.h"
#include "Core.h"

CCore::CCore()
	: m_hdc(NULL), m_memDC(NULL)
{
}

CCore::~CCore()
{
	ReleaseDC(g_hWnd, m_hdc);
	DeleteDC(m_memDC);
}

void CCore::init()
{
	// ���� ���۸�,  ���� �����쿡 ���� DC(main DC)�� ������ �´�
	m_hdc = ::GetDC(g_hWnd);

	// main DC�� ����, m_memDC: �޸𸮿� �׷��� DC
	m_memDC = CreateCompatibleDC(m_hdc);

	// main DC�� ȣȯ���� �ִ� ��Ʈ���� �߰��� ����
	HBITMAP bitmap = CreateCompatibleBitmap(m_hdc, WINSIZE_X, WINSIZE_Y);
	HBITMAP oldBit = (HBITMAP)SelectObject(m_memDC, bitmap); // ��ȭ�� setting
	DeleteObject(oldBit);
}

int CCore::progress()
{
	update();

	render();

	return 0;
}

int CCore::update()
{
	return 0;
}

void CCore::render()
{
	RECT rect;	GetClientRect(g_hWnd, &rect); // window�� �ʺ�� ���̸� ����
	Rectangle(m_memDC, 0, 0, WINSIZE_X + 1, WINSIZE_Y + 1); // ������ â ȭ���� �Ͼ�� �ϱ� ���� Rectangle�� �׸�
	BitBlt(m_hdc, 0, 0, rect.right, rect.bottom, m_memDC, 0, 0, SRCCOPY); // �̹����� ȭ�鿡 ����ϴ� �Լ�
}