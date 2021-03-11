#pragma once

#include "Border.h"

class CCollisionObj;

class CCollision
{
protected:
	static WORD		g_iNextID;

protected:
	CCollisionObj*		m_pOwner;
	WORD					m_iColID;
	tColInfo					m_ColInfo; // 충돌체의 정보 : 위치 크기 모양 옾셋  등등
	CBorder					m_Border;

public:
	WORD GetColID() { return m_iColID; }
	COL_TYPE GetColType() { return m_ColInfo.eType; } // SetColType이 없는 대신 무조건 생성자에서 받게 한다.
													  // 우리가 구현한 tagPoint들의 덧셈을 연산 하므로 우리 tagPoint에도 +operator를 구현해야한다.
													  
	tPoint GetColPos() { return m_ColInfo.ptPos + m_ColInfo.ptOffset; } // 충돌을 확인해야 하는 위치는 충돌체의 위치와 옾셋을 더한 위치
	tPoint GetSize() { return m_ColInfo.ptSize; }

	void SetCollisionInfo(const tColInfo& _info); // CCollisionObj들의 Collision을 정보를 초기화
																 // ex) CPlayer::init()에 m_Collision.SetCollisionInfo( .. );
	CCollisionObj* GetpOwner() { return m_pOwner; }
public:
	int update();
	void render(HDC _dc);

public:
	virtual void OnCollisionEnter(CCollision* _pOther);
	virtual void OnCollision(CCollision* _pOther);
	virtual void OnCollisionExit(CCollision* _pOther);

public:
	CCollision(CCollisionObj* m_pOwner);
	virtual ~CCollision();
};