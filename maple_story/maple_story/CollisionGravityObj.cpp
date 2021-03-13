#include "pch.h"
#include "CollisionGravityObj.h"

CCollisionGravityObj::CCollisionGravityObj(wstring _strObjTag, tPoint _ptPos)
	:CCollisionObj(_strObjTag, _ptPos),
	m_iHorizonSpeed(100), m_iVerticalSpeed(100), m_bGround(false)
{
}

CCollisionGravityObj::~CCollisionGravityObj()
{
}

int CCollisionGravityObj::update()
{
	return 0;
}

void CCollisionGravityObj::render(HDC _dc)
{
}

void CCollisionGravityObj::CheckGround()
{
	if (m_ptPos.fY < WINSIZE_Y - (PLAYER_SIZE * 1))
		m_bGround = false;
	else
	{
		if (m_bGround)
			return;
		
		/* ���� ������ ���ʿ� �ٽ� �ʱ�ȭ*/
		m_bGround = true;
		m_iVerticalSpeed = 0;

		for (int i = 0; i < m_vecPostGround.size(); ++i)
		{
			(this->m_vecPostGround[i])(); //��� �Լ� �����Ͱ� �ƴϹǷ� ->* �� �ƴ� -> 
		}
	}
}