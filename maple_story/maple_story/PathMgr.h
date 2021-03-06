#pragma once

class CPathMgr
{
private:
	static wchar_t m_strResPath[MAX_STR];
	//wchar_t: 아스키 코드로 표현할 수 없는 국제문자를 다루기 위한 자료형

public:
	static void init();
	static wchar_t* GetResourcesPath() { return m_strResPath; };
	static void GetPrevPath(wchar_t*, int _iSize);  

public:
	CPathMgr();
	~CPathMgr();
};