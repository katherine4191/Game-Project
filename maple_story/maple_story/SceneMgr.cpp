#include "pch.h"
#include "SceneMgr.h"

CSceneMgr::CSceneMgr(): m_pCurScene(NULL), m_pPrevScene(NULL)
{
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

CSceneMgr::~CSceneMgr()
{
}
