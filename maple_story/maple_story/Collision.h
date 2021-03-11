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
	tColInfo					m_ColInfo; // �浹ü�� ���� : ��ġ ũ�� ��� ����  ���
	CBorder					m_Border;

public:
	WORD GetColID() { return m_iColID; }
	COL_TYPE GetColType() { return m_ColInfo.eType; } // SetColType�� ���� ��� ������ �����ڿ��� �ް� �Ѵ�.
													  // �츮�� ������ tagPoint���� ������ ���� �ϹǷ� �츮 tagPoint���� +operator�� �����ؾ��Ѵ�.
													  
	tPoint GetColPos() { return m_ColInfo.ptPos + m_ColInfo.ptOffset; } // �浹�� Ȯ���ؾ� �ϴ� ��ġ�� �浹ü�� ��ġ�� ������ ���� ��ġ
	tPoint GetSize() { return m_ColInfo.ptSize; }

	void SetCollisionInfo(const tColInfo& _info); // CCollisionObj���� Collision�� ������ �ʱ�ȭ
																 // ex) CPlayer::init()�� m_Collision.SetCollisionInfo( .. );
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