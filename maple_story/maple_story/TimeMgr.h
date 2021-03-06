#pragma once
class CTimeMgr
{
	SINGLETONE(CTimeMgr)

private:
	LARGE_INTEGER	m_llCurCnt;
	LARGE_INTEGER	m_llLastCnt;
	LARGE_INTEGER	m_llFrequency;
	float			m_fDeltaTime;

public:
	float	DeltaTime() { return m_fDeltaTime; }

public:
	void init();
	int update();

private:
	CTimeMgr();
	~CTimeMgr();
};

