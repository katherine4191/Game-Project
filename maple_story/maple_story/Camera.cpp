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
	// ���� ���� ���� ��ġ�� ī�޶� �������� ������ ��ġ�� ��ȯ
	return tPoint(_ptRealPos.fX - m_ptDiff.fX, _ptRealPos.fY - m_ptDiff.fY);
}

POINT CCamera::GetMousePos()
{
	// ���콺 ��ġ�� ���� ī�޶� �������� ����
	POINT pt;
	GetCursorPos(&pt);
	// ScreenToClient: ��ü ȭ�� ������ Ŀ���� ��ǥ�� �ش� Ŭ���̾�Ʈ(������) �������� ��ǥ�� ��ȯ���ִ� �Լ�
	ScreenToClient(g_hWnd, &pt); 

	pt.x += (int)m_ptDiff.fX;
	pt.y += (int)m_ptDiff.fY;

	return pt;
}