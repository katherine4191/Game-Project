#pragma once

class CPathMgr
{
private:
	static wchar_t m_strResPath[MAX_STR];
	//wchar_t: �ƽ�Ű �ڵ�� ǥ���� �� ���� �������ڸ� �ٷ�� ���� �ڷ���

public:
	static void init();
	static wchar_t* GetResourcesPath() { return m_strResPath; };
	static void GetPrevPath(wchar_t*, int _iSize);  

public:
	CPathMgr();
	~CPathMgr();
};