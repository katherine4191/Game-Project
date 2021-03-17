#pragma once
#include "CollisionGravityObj.h"

class CTexture;

class CMonster :
	public CCollisionGravityObj
{
private:
	CAnimator* m_pAnimator;

	MONSTER_MOTION_TYPE     m_ePMotionType;
	bool                    m_arrMotionProgress[(int)MONSTER_MOTION_TYPE::END];

public:
	virtual void init();
	virtual int update();
	virtual void render(HDC _dc);
	virtual void CheckGround();

public:
	void SetMotionType(MONSTER_MOTION_TYPE _eType);

private:
	void ControlMotionRender();

public:
	//CMonster();
	CMonster(wstring _strObjTag, tPoint _ptPos);
	virtual ~CMonster();
};



