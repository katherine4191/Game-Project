#include "pch.h"
#include "ResMgr.h"

#include "PathMgr.h"
#include "Texture.h"

CResMgr::CResMgr()
{
}

CResMgr::~CResMgr()
{
	Safe_Delete_Map(m_mapTex);
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strPath)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

	if (iter != m_mapTex.end()) // 이미 load한 적 있는 texture
		return iter->second;

	if (!_strPath.length())
		return NULL; 
		
	wstring strFullPath = CPathMgr::GetResourcesPath();
	strFullPath += _strPath;

	CTexture* pTex = new CTexture;
	if (!pTex->Load(strFullPath)) // Tex Load Fail
	{
		delete pTex;
		wstring msg = L"Texture Loading Fail : ";
		msg += _strPath;
		MessageBox(NULL, msg.c_str(), L"텍스쳐 로딩 실패", MB_OK);
		return NULL;
	}

	pTex->SetKey(_strKey);
	pTex->SetPath(_strPath);
	m_mapTex.insert(make_pair(_strKey, pTex));
	return pTex;
}
