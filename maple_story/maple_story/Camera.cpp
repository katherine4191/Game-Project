#include "pch.h"
#include "Camera.h"

CCamera::CCamera()
	: m_ptFocus(tPoint(0.f, 0.f)), m_ptDiff(tPoint(0.f, 0.f))
{}

CCamera::~CCamera()
{}

void CCamera::init()
{
	m_ptFocus.fX = WINSIZE_X / 2.f;
	m_ptFocus.fY = WINSIZE_Y / 2.f;
}

int CCamera::update()
{
	m_ptDiff.fX = m_ptFocus.fX - (WINSIZE_X / 2.f);
	m_ptDiff.fY = m_ptFocus.fY - (WINSIZE_Y / 2.f);
	return 0;
}

tPoint CCamera::GetStdCamPos(tPoint _ptRealPos)
{
	// 게임 상의 실제 위치를 카메라 기준으로 보정한 위치를 반환
	return tPoint(_ptRealPos.fX - m_ptDiff.fX, _ptRealPos.fY - m_ptDiff.fY);
}

POINT CCamera::GetMousePos()
{
	// 마우스 위치를 얻어와 카메라 기준으로 변경
	POINT pt;
	GetCursorPos(&pt);
	// ScreenToClient: 전체 화면 기준인 커서의 좌표를 해당 클라이언트(윈도우) 기준으로 좌표를 변환해주는 함수
	ScreenToClient(g_hWnd, &pt); 

	pt.x += (int)m_ptDiff.fX;
	pt.y += (int)m_ptDiff.fY;

	return pt;
}