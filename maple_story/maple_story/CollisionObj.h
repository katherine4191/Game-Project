#pragma once

#include "Obj.h"
#include "Collision.h" 
#include "AttackBox.h"


class CCollisionObj :
	public CObj
{
protected:
	CCollision					m_Collision;
	CAttackBox					m_AttackCollision;
	tInfo						m_tInfo; // EXP, MP, HP 내가 만든 구조체가 아님

	vector<function<CCollision* (void)>>				  m_vecGetCollision;

protected:
	virtual int update();
	virtual void render(HDC _dc);

public:
	const tInfo& GetInfo() { return m_tInfo; }
	void SetInfo(const tInfo& _info) { m_tInfo = _info; }
	virtual bool IsCollision() { return true; }
	CCollision* GetCollision() { return &m_Collision; }
	CAttackBox* GetAttackBox() { return &m_AttackCollision; }
	const vector<function<CCollision* (void)>>& GetvecCollision() { return m_vecGetCollision; }

	void SetAttackBoxActive(bool _bActive) { m_AttackCollision.SetbActive(_bActive); }


	virtual void OnCollisionEnter() {};
	virtual void OnCollision() {};
	virtual void OnCollisionExit() {};

public:
	//CCollisionObj(); //(wstring _strObjTag, tPoint _ptPos)
	CCollisionObj(wstring _strObjTag, tPoint _ptPos);
	virtual ~CCollisionObj();
};

