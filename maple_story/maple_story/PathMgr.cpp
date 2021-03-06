#include "pch.h"
#include "PathMgr.h"

wchar_t CPathMgr::m_strResPath[MAX_STR] = { 0 };

CPathMgr::CPathMgr()
{
}

CPathMgr::~CPathMgr()
{
}

void CPathMgr::init()
{
	GetCurrentDirectory(MAX_STR, m_strResPath);
	GetPrevPath(m_strResPath, MAX_STR);
	wcscat_s(m_strResPath, L"Bin\\Resources\\");
}

void CPathMgr::GetPrevPath(wchar_t* _pStr, int _iSize)
{
	// _pStr에 현재 경로의 상위 폴더의 경로로 변경
	int iLen = wcslen(_pStr);
	for (int i = iLen - 1; i >= 0; --i)
	{
		if (_pStr[i] == '\\')
		{
			wmemset(_pStr + i + 1, 0, iLen - (i + 1));
			return;
		}
	}
}