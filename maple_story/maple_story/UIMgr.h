#pragma once
class CUI;

class CUIMgr
{
	SINGLETONE(CUIMgr)

private:
	map<CUI*, tUIState>		m_mapUI;

public:
	void init();
	int update();

public:
	CUIMgr();
	~CUIMgr();
};