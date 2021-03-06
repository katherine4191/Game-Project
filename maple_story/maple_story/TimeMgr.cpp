#include "pch.h"
#include "TimeMgr.h"

CTimeMgr::CTimeMgr()
	:m_fDeltaTime(0.f)
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::init()
{
	QueryPerformanceFrequency(&m_llFrequency); // �ʴ� ������	
	QueryPerformanceCounter(&m_llCurCnt); // ���ݱ��� ī��Ʈ(���� �ð� üũ �Լ�)
	update();
}

int CTimeMgr::update()
{
	// Counter ���� ���� ���μ��������� QueryPerformanceFrequency�� ���� PerformanceCounter ���ļ� ������ ������ ���� �ð��� �ȴ�.
	QueryPerformanceCounter(&m_llCurCnt);
	m_fDeltaTime = (float)(m_llCurCnt.QuadPart - m_llLastCnt.QuadPart) / (float)m_llFrequency.QuadPart;
	QueryPerformanceCounter(&m_llLastCnt);
	return 0;
}