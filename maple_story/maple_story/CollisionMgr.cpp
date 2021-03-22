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
	// ���� �ش��ϴ� Scene�� �ҷ��´�.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// �ش��ϴ� �ε����� �ش��ϴ� ���̾ �ҷ��´�.
	CLayer* pLeftLayer = pCurScene->FindLayer(_iLeftIdx);
	CLayer* pRightLayer = pCurScene->FindLayer(_iRightIdx);

	// ���̾� ���� object list�� �ҷ��´�.
	const list<CObj*>& listLeft = pLeftLayer->GetObjList();
	const list<CObj*>& listRIght = pRightLayer->GetObjList();

	// object list���� iterator�� ��ȸ�ϸ鼭 
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
				// for�� ����..��
				for (int i = 0; i < ((CCollisionObj*)(*leftIter))->GetvecCollision().size(); ++i)
				{
					// GetvecCollision()[i]()�� ()�� ������ �ʵ��� ����!
					CCollision* pLeftCol = ((CCollisionObj*)(*leftIter))->GetvecCollision()[i]();
					CCollision* pRightCol = ((CCollisionObj*)(*rightIter))->GetvecCollision()[i]();

					// if ���ȿ� ����� �κ��� ������ �ϰ�,
					// ����: (pLeftCol->GetColID(), pRightCol->GetColID())�̴�! �׳ɤ���
					COL_ID id = MakeCollisonID(pLeftCol->GetColID(), pRightCol->GetColID());

					// �浹 �ߴ�.
					if (CollisionObject(pLeftCol, pRightCol))
					{
						map<COL_ID, bool>::iterator map_iter = m_mapCol.find(id);

						// case 1. map �� id ������ �������� �ʾ��� ���
						//  - ���� �浹�̴�
						//  - m_mapCol �� id ���(true)
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
								// case 2. map �� �־�, second -> false
								//  - �浹 ����
								//  - second �� true
								pLeftCol->OnCollisionEnter(pRightCol);
								pRightCol->OnCollisionEnter(pLeftCol);
							}
							else
							{
								// case 3. map �� �־�, second -> true
								//  - �������� �浹 ���̾���.
								pLeftCol->OnCollision(pRightCol);
								pRightCol->OnCollision(pLeftCol);
							}
							map_iter->second = true;
						}
					}

					// �浹���� �ʾҴ�.
					else
					{
						map<COL_ID, bool>::iterator map_iter = m_mapCol.find(id);
						if (map_iter != m_mapCol.end() && map_iter->second)
						{
							// map �� �־�, second �� true
							// �浹�� �� ��� ����
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
	// �� �浹ü�� �� �簢���� �� 
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
	// �� �浹ü�� �� ���� �� 
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
	// �� �浹ü�� �簢���̰� �ٸ� �浹ü�� ���� �� 
	tPoint ptLeftPos = _pLeftCol->GetColPos();
	tPoint ptRightPos = _pRightCol->GetColPos();
	return false;
}