#pragma once
#include "Collision.h"
class CCollisionObj;
// 원래는 class CCollisionGravityObj;

class CAttackBox :
	public CCollision
{
protected:
	bool		m_bActive; // 충돌체를 on, off해주는 bool 변수

public:
	int update();
	void render(HDC _dc);

public:
	virtual void OnCollisionEnter(CCollision* _pOther);
	virtual void OnCollision(CCollision* _pOther);
	virtual void OnCollisionExit(CCollision* _pOther);

public:
	void SetbActive(bool _bActive) { m_bActive = _bActive; }
public:
	CAttackBox(CCollisionObj* _pOwner);
	virtual ~CAttackBox();
};

