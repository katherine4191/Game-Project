#include "pch.h"
#include "Scene.h"

CScene::CScene()
	:m_iNextIdx(0)
{
}

CScene::~CScene()
{
	map<wstring, tLayerInfo>::iterator iter = m_mapLayer.begin();
	for (; iter != m_mapLayer.end(); ++iter)
	{
		SAFE_DELETE(iter->second.pLayer);
	}
}

int CScene::update()
{
	return 0;
}

void CScene::render(HDC)
{
}

void CScene::AddLayer(const wstring& _strLayerName)
{
}

bool CScene::AddObject(const wstring& _strLayerName, CObj* _pObj)
{
	return false;
}

bool CScene::DeleteObjects(const wstring& _strLayerName)
{
	return false;
}

CObj* CScene::FindObject(const wstring& _strTag)
{
	return nullptr;
}

CObj* CScene::FindObject(const wstring& _strLayerName, const wstring& _strTag)
{
	return nullptr;
}

int CScene::GetLayerIndex(const wstring& _strLayerName)
{
	return 0;
}

CLayer* CScene::FindLayer(const wstring& _strLayerName)
{
	return nullptr;
}

CLayer* CScene::FindLayer(int _iIdx)
{
	return nullptr;
}

