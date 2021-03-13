#pragma once
#include "CollisionObj.h"

class CCollisionGravityObj :
		public CCollisionObj
{
protected:
	bool												m_bGround;
	vector<function<void(void)>>			m_vecPostGround;
	int													m_iHorizonSpeed;
	int													m_iVerticalSpeed;

public:
	virtual int update();
	virtual void render(HDC _dc);
	void CheckGround();

public:
	//CCollisionGravityObj();
	CCollisionGravityObj(wstring _strObjTag, tPoint _ptPos);
	virtual ~CCollisionGravityObj();
};

