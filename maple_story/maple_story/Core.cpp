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
	// 더블 버퍼링,  메인 윈도우에 대한 DC(main DC)를 가지고 온다
	m_hdc = ::GetDC(g_hWnd);

	// main DC를 복사, m_memDC: 메모리에 그려줄 DC
	m_memDC = CreateCompatibleDC(m_hdc);

	// main DC에 호환성이 있는 비트맵을 추가로 생성
	HBITMAP bitmap = CreateCompatibleBitmap(m_hdc, WINSIZE_X, WINSIZE_Y);
	HBITMAP oldBit = (HBITMAP)SelectObject(m_memDC, bitmap); // 도화지 setting
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
	RECT rect;	GetClientRect(g_hWnd, &rect); // window의 너비와 높이를 구함
	Rectangle(m_memDC, 0, 0, WINSIZE_X + 1, WINSIZE_Y + 1); // 윈도우 창 화면이 하얗게 하기 위해 Rectangle을 그림
	BitBlt(m_hdc, 0, 0, rect.right, rect.bottom, m_memDC, 0, 0, SRCCOPY); // 이미지를 화면에 출력하는 함수
}