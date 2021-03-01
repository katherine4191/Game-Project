#include "pch.h"
#include "SceneMgr.h"

CSceneMgr::CSceneMgr()
	: m_pCurScene(NULL), m_pPrevScene(NULL)
{
	memset(m_arrScene, 0, sizeof(void*) * (int)SCENE_TYPE::END);
}

CSceneMgr::~CSceneMgr()
{
	for (int i = 0; i < (int)SCENE_TYPE::END; ++i)
	{
		SAFE_DELETE(m_arrScene[i]);
	}
}

void CSceneMgr::init()
{
}

int CSceneMgr::update()
{
	return 0;
}

void CSceneMgr::render(HDC _dc)
{
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNextScene)
{
}

void CSceneMgr::AddObject(const wstring& _strLayerName, CObj* _pObj)
{
}

CObj* CSceneMgr::FindObject(const wstring& _strTag)
{
	return nullptr;
}

CObj* CSceneMgr::FindObject(const wstring& _strLayerName, const wstring& _strTag)
{
	return nullptr;
}

