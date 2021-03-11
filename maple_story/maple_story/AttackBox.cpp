#include "pch.h"
#include "AttackBox.h"

#include "Collision.h"
#include "CollisionObj.h"

//#include "Animator.h"
//#include "Monster.h"

CAttackBox::CAttackBox(CCollisionObj* _pOwner)
	: CCollision(_pOwner), m_bActive(false)
{
}

CAttackBox::~CAttackBox()
{
}

int CAttackBox::update()
{
	CCollision::update();
	return 0;
}

void CAttackBox::render(HDC _dc)
{
	CCollision::render(_dc);
}

void CAttackBox::OnCollisionEnter(CCollision* _pOther)
{
	CCollisionObj* pTemp = _pOther->GetpOwner();
	wstring ObjName = pTemp->GetTag();
	//if (ObjName == L"Monster")
	//{
	//	CMonster* pMonster = (CMonster*)pTemp;
	//	pMonster->SetMotionType(MONSTER_MOTION_TYPE::ATTACKED_LEFT);
	//}

}

void CAttackBox::OnCollision(CCollision* _pOther)
{
	int c = 9;
}

void CAttackBox::OnCollisionExit(CCollision* _pOther)
{
}
