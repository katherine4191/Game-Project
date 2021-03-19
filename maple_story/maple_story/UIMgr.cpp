#include "pch.h"
#include "UIMgr.h"

#include "SceneMgr.h"
#include "scene.h"
#include "Layer.h"
#include "UI.h"

CUIMgr::CUIMgr()
{
}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::init()
{
	m_mapUI.clear();

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pUILayer = pCurScene->FindLayer(L"UI");

	if (NULL == pUILayer)
		return;

	list<CObj*>& _list = pUILayer->GetObjList();

	list<CObj*>::iterator iter = _list.begin();
	for (; iter != _list.end(); ++iter)
	{
		m_mapUI.insert(make_pair((CUI*)(*iter), tUIState()));
	}
}

int CUIMgr::update()
{
	map<CUI*, tUIState>::iterator iter = m_mapUI.begin();
	for (; iter != m_mapUI.end(); ++iter)
	{
		if (iter->first->IsMouseOn()) // 마우스가 해당 UI 에 최초로 올라간 시점	
		{
			if (!iter->second.bMouseOn)
			{
				iter->first->OnMouseFirst();
			}
			else
			{
				iter->first->OnMouse();
			}
			iter->second.bMouseOn = true; // 현재 UI 상태 갱신
		}
		else
		{
			if (iter->second.bMouseOn)
				iter->first->OnMouseOut();
			iter->second.bMouseOn = false;
		}

		if (iter->first->IsLBtnClicked())
		{
			if (!iter->second.bLBtnClicked)
			{
				iter->first->OnMouseLBtnDown();
			}
			else
			{

			}
			iter->second.bLBtnClicked = true;
		}
		else
		{
			if (iter->second.bLBtnClicked && iter->first->IsMouseOn())
				iter->first->OnMouseLBtnUp();
			iter->second.bLBtnClicked = false;
		}
	}
	return 0;
}