#include "pch.h"
#include "Layer.h"

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
	Safe_Delete_list(m_listObj);
}

int CLayer::update()
{
	return 0;
}

void CLayer::render(HDC _dc)
{
}

void CLayer::AddObject(CObj* _pObj)
{
}

void CLayer::DeleteObjects()
{
}