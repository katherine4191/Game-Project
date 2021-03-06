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
	QueryPerformanceFrequency(&m_llFrequency); // 초당 진동수	
	QueryPerformanceCounter(&m_llCurCnt); // 지금까지 카운트(고성능 시간 체크 함수)
	update();
}

int CTimeMgr::update()
{
	// Counter 값을 현재 프로세서에서의 QueryPerformanceFrequency로 얻은 PerformanceCounter 주파수 값으로 나누면 현재 시간이 된다.
	QueryPerformanceCounter(&m_llCurCnt);
	m_fDeltaTime = (float)(m_llCurCnt.QuadPart - m_llLastCnt.QuadPart) / (float)m_llFrequency.QuadPart;
	QueryPerformanceCounter(&m_llLastCnt);
	return 0;
}