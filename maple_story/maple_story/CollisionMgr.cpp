#include "pch.h"
#include "CollisionMgr.h"

#include "scenemgr.h"
#include "Scene.h"
#include "Layer.h"
#include "obj.h"

#include "collisionobj.h"
#include "collision.h"


CCollisionMgr::CCollisionMgr()
{
	memset(m_arrBit, 0, sizeof(BYTE) * 8);
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CheckCollision(const wstring& _strLayer1, const wstring& _strLayer2)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	if (NULL == pCurScene)
		return;

	int iLeftLayer = pCurScene->GetLayerIndex(_strLayer1);
	int iRightLayer = pCurScene->GetLayerIndex(_strLayer2);

	if (iLeftLayer > iRightLayer)
	{
		int iTemp = iLeftLayer;
		iLeftLayer = iRightLayer;
		iRightLayer = iTemp;
	}

	m_arrBit[iLeftLayer] |= (1 << iRightLayer);
}

int CCollisionMgr::update()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = i; j < 8; ++j)
		{
			if (m_arrBit[i] & (1 << j))
				CollisionLayer(i, j);
		}
	}
	return 0;
}

void CCollisionMgr::CollisionLayer(int _iLeftIdx, int _iRightIdx)
{
	// 현재 해당하는 Scene을 불러온다.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// 해당하는 인덱스에 해당하는 레이어를 불러온다.
	CLayer* pLeftLayer = pCurScene->FindLayer(_iLeftIdx);
	CLayer* pRightLayer = pCurScene->FindLayer(_iRightIdx);

	// 레이어 안의 object list를 불러온다.
	const list<CObj*>& listLeft = pLeftLayer->GetObjList();
	const list<CObj*>& listRIght = pRightLayer->GetObjList();

	// object list들을 iterator로 순회하면서 
	list<CObj*>::const_iterator leftIter = listLeft.begin();
	list<CObj*>::const_iterator rightIter;

	for (; leftIter != listLeft.end(); ++leftIter)
	{
		rightIter = listRIght.begin();
		for (; rightIter != listRIght.end(); ++rightIter)
		{
			if ((*leftIter)->IsCollision() && (*rightIter)->IsCollision())
			{
				//CCollision* pLeftCol = ((CCollisionObj*)(*leftIter))->GetCollision();
				//CCollision* pRightCol = ((CCollisionObj*)(*rightIter))->GetCollision();
				//CCollision* pLeftCol = ((CCollisionObj*)(*leftIter))->GetAttackBox();
				//CCollision* pRightCol = ((CCollisionObj*)(*rightIter))->GetAttackBox();

				//////////////////////////////////////////////////////////////////////////////
				// for문 생김..ㅎ
				for (int i = 0; i < ((CCollisionObj*)(*leftIter))->GetvecCollision().size(); ++i)
				{
					// GetvecCollision()[i]()의 ()를 빼먹지 않도록 하자!
					CCollision* pLeftCol = ((CCollisionObj*)(*leftIter))->GetvecCollision()[i]();
					CCollision* pRightCol = ((CCollisionObj*)(*rightIter))->GetvecCollision()[i]();

					// if 문안에 공통된 부분은 빼도록 하고,
					// 인자: (pLeftCol->GetColID(), pRightCol->GetColID())이다! 그냥ㅎㅎ
					COL_ID id = MakeCollisonID(pLeftCol->GetColID(), pRightCol->GetColID());

					// 충돌 했다.
					if (CollisionObject(pLeftCol, pRightCol))
					{
						map<COL_ID, bool>::iterator map_iter = m_mapCol.find(id);

						// case 1. map 에 id 조합이 존재하지 않았을 경우
						//  - 최초 충돌이다
						//  - m_mapCol 에 id 등록(true)
						if (map_iter == m_mapCol.end())
						{
							pLeftCol->OnCollisionEnter(pRightCol);
							pRightCol->OnCollisionEnter(pLeftCol);
							m_mapCol.insert(make_pair(id, true));
						}
						else
						{
							if (!map_iter->second)
							{
								// case 2. map 에 있어, second -> false
								//  - 충돌 진입
								//  - second 를 true
								pLeftCol->OnCollisionEnter(pRightCol);
								pRightCol->OnCollisionEnter(pLeftCol);
							}
							else
							{
								// case 3. map 에 있어, second -> true
								//  - 이전에도 충돌 중이었다.
								pLeftCol->OnCollision(pRightCol);
								pRightCol->OnCollision(pLeftCol);
							}
							map_iter->second = true;
						}
					}

					// 충돌하지 않았다.
					else
					{
						map<COL_ID, bool>::iterator map_iter = m_mapCol.find(id);
						if (map_iter != m_mapCol.end() && map_iter->second)
						{
							// map 에 있어, second 가 true
							// 충돌이 막 벗어난 시점
							pLeftCol->OnCollisionExit(pRightCol);
							pRightCol->OnCollisionExit(pLeftCol);
							map_iter->second = false;
						}
					}
				}
			}
		}
	}
}

bool CCollisionMgr::CollisionObject(CCollision* _pLeftCol, CCollision* _pRightCol)
{
	if (_pLeftCol->GetColType() == COL_TYPE::RECTANGLE
		&& _pRightCol->GetColType() == COL_TYPE::RECTANGLE)
	{
		return RtoRCollision(_pLeftCol, _pRightCol);
	}
	else
	{
		if (_pLeftCol->GetColType() == COL_TYPE::CIRCLE
			&& _pRightCol->GetColType() == COL_TYPE::CIRCLE)
		{
			return CtoCCollision(_pLeftCol, _pRightCol);
		}
		else
		{
			return RtoCCollision(_pLeftCol, _pRightCol);
		}
	}
	return true;
}

bool CCollisionMgr::RtoRCollision(CCollision* _pLeftCol, CCollision* _pRightCol)
{
	// 두 충돌체가 다 사각형일 때 
	tPoint ptLeftPos = _pLeftCol->GetColPos();
	tPoint ptRightPos = _pRightCol->GetColPos();

	if ((abs(ptLeftPos.fX - ptRightPos.fX) <= _pLeftCol->GetSize().fX / 2.f + _pRightCol->GetSize().fX / 2.f)
		&& (abs(ptLeftPos.fY - ptRightPos.fY) <= _pLeftCol->GetSize().fY / 2.f + _pRightCol->GetSize().fY / 2.f))
	{
		return true;
	}
	return false;
}

bool CCollisionMgr::CtoCCollision(CCollision* _pLeftCol, CCollision* _pRightCol)
{
	// 두 충돌체가 다 원일 때 
	tPoint ptLeftPos = _pLeftCol->GetColPos();
	tPoint ptRightPos = _pRightCol->GetColPos();

	float fRadius = _pLeftCol->GetSize().fY / 2;
	float fDistance = sqrtf((ptLeftPos.fX - ptRightPos.fX) * (ptLeftPos.fX - ptRightPos.fX) + (ptLeftPos.fY - ptRightPos.fY) * (ptLeftPos.fY - ptRightPos.fY));
	if (fDistance < 2 * fRadius)
	{
		return true;
	}
	return false;
}

bool CCollisionMgr::RtoCCollision(CCollision* _pLeftCol, CCollision* _pRightCol)
{
	// 한 충돌체가 사각형이고 다른 충돌체가 원일 때 
	tPoint ptLeftPos = _pLeftCol->GetColPos();
	tPoint ptRightPos = _pRightCol->GetColPos();
	return false;
}