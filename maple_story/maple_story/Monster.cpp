#include "pch.h"
#include "Monster.h"

#include "Animator.h"

CMonster::CMonster(wstring _strObjTag, tPoint _ptPos)
	:CCollisionGravityObj(_strObjTag, _ptPos), m_ePMotionType(MONSTER_MOTION_TYPE::STAND_LEFT)
{
	m_ptPos = tPoint(WINSIZE_X - WINSIZE_X / 4, WINSIZE_Y - MONSTER_SIZE);
	m_pAnimator = GetAnimator();
}

CMonster::~CMonster()
{
}

void CMonster::init()
{
	// Animation �ε�
	m_pAnimator->LoadAnimation(L"Animation\\M_MR_Attacked_Left.anim");
	m_pAnimator->LoadAnimation(L"Animation\\M_MR_Stand_Left.anim");

	// Collision ���� ����
	m_Collision.SetCollisionInfo(tColInfo(COL_TYPE::CIRCLE, m_ptPos, tPoint(-1.f, 0.f), tPoint(64.f, 64.f)));
	m_AttackCollision.SetCollisionInfo(tColInfo(COL_TYPE::RECTANGLE, m_ptPos, tPoint(-1.f, 0.f), tPoint(64.f, 64.f)));

	//functional
}

void CMonster::SetMotionType(MONSTER_MOTION_TYPE _eType)
{
	m_ePMotionType = _eType;
	m_arrMotionProgress[(int)_eType] = true;
}

int CMonster::update()
{
	if (m_pAnimator->IsAnimFinish(L"M_MR_Attacked_Left"))
	{
		SetMotionType(MONSTER_MOTION_TYPE::STAND_LEFT);
		m_pAnimator->SetAnimbFinish(L"M_MR_Attacked_Left", false);
	}

	m_pAnimator->update();
	CCollisionObj::update();
	return 0;
}

void CMonster::render(HDC _dc)
{
	ControlMotionRender();
	m_pAnimator->render(_dc);
	CCollisionObj::render(_dc);
}

void CMonster::CheckGround()
{
}

void CMonster::ControlMotionRender()
{
	int arrIdx = (int)MONSTER_MOTION_TYPE::END;
	for (int i = 0; i < arrIdx; ++i)
	{
		if (m_arrMotionProgress[i])
		{
			if (i == (int)MONSTER_MOTION_TYPE::STAND_LEFT)
				m_pAnimator->PlayAnimation(L"M_MR_Stand_Left", true);
			else if (i == (int)MONSTER_MOTION_TYPE::ATTACKED_LEFT)
				m_pAnimator->PlayAnimation(L"M_MR_Attacked_Left", false);

			// ���⿡ ���Դٴ� �� true��� ���̴�. 
			m_arrMotionProgress[i] = 0;
		}
	}
}
