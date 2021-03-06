#pragma once

class CTexture;

class CResMgr
{
	SINGLETONE(CResMgr)

private:
	map<wstring, CTexture*>		m_mapTex;

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strPath = L"");

private:
	CResMgr();
	~CResMgr();
};

