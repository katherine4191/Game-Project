#include "pch.h"
#include "CollisionObj.h"

//CCollisionObj::CCollisionObj()
//	: m_Collision(this) , m_AttackCollision(this) //Collision* 아닌 Collision을 가지므로
//{
//	memset(&m_tInfo, 0, sizeof(tInfo));
//	m_vecGetCollision.push_back(bind(&CCollisionObj::GetCollision, this));
//	m_vecGetCollision.push_back(bind(&CCollisionObj::GetAttackBox, this));
//
//	//m_vecGetCollision.push_back(bind(&GetCollision, this));
//	//m_vecGetCollision.push_back(bind(&GetAttackBox, this));
//
//}

CCollisionObj::CCollisionObj(wstring _strObjTag, tPoint _ptPos)
	:CObj(_strObjTag, _ptPos), m_Collision(this), m_AttackCollision(this)
{
	memset(&m_tInfo, 0, sizeof(tInfo));
	m_vecGetCollision.push_back(bind(&CCollisionObj::GetCollision, this));
	m_vecGetCollision.push_back(bind(&CCollisionObj::GetAttackBox, this));
}

CCollisionObj::~CCollisionObj()
{
}

int CCollisionObj::update()
{
	m_Collision.update();
	m_AttackCollision.update();
	return 0;
}

void CCollisionObj::render(HDC _dc)
{
	m_Collision.render(_dc);
	m_AttackCollision.render(_dc);
}