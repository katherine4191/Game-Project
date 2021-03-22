#pragma once

class CCollision;

union COL_ID
{
	DWORD ID;
	struct {
		WORD leftID;
		WORD rightID;
	} tID;

	// map에 insert할 때 map은 이진 탐색 트리이므로 무엇이 큰 지에 대한 기분을 정확히 명시해야한다.
	bool operator < (const COL_ID& _id) const // const를 붙이게 되면 이 안에 잇는 모든 코드의 자기자신을 수정하지 못한다. 
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
		// rightID가 큰 것,leftID가 작은 것이 들어가는 것이 원칙이다.
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

