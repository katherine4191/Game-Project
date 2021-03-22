#pragma once

class CCollision;

union COL_ID
{
	DWORD ID;
	struct {
		WORD leftID;
		WORD rightID;
	} tID;

	// map�� insert�� �� map�� ���� Ž�� Ʈ���̹Ƿ� ������ ū ���� ���� ����� ��Ȯ�� ����ؾ��Ѵ�.
	bool operator < (const COL_ID& _id) const // const�� ���̰� �Ǹ� �� �ȿ� �մ� ��� �ڵ��� �ڱ��ڽ��� �������� ���Ѵ�. 
	{
		if (ID < _id.ID)
			return true;
		return false;
	}
};

class CCollisionMgr
{
	SINGLETONE(CCollisionMgr)

private:
	BYTE				m_arrBit[sizeof(BYTE) * 8];
	map<COL_ID, bool>	m_mapCol;

public:
	void CheckCollision(const wstring& _strLayer1, const wstring& _strLayer2);
	int update();

private:
	void CollisionLayer(int _iLeftIdx, int _iRightIdx);
	bool CollisionObject(CCollision* _pLeftCol, CCollision* _pRightCol);
	bool RtoRCollision(CCollision* _pLeftCol, CCollision* _pRightCol);
	bool CtoCCollision(CCollision* _pLeftCol, CCollision* _pRightCol);
	bool RtoCCollision(CCollision* _pLeftCol, CCollision* _pRightCol);

	COL_ID MakeCollisonID(WORD _iLeft, WORD _iRight)
	{
		COL_ID id;
		// rightID�� ū ��,leftID�� ���� ���� ���� ���� ��Ģ�̴�.
		if (_iLeft <= _iRight)
		{
			id.tID.leftID = _iLeft;
			id.tID.rightID = _iRight;
		}
		else
		{
			id.tID.leftID = _iRight;
			id.tID.rightID = _iLeft;
		}
		return id;
	}


public:
	CCollisionMgr();
	~CCollisionMgr();
};

