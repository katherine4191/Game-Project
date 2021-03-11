#pragma once
typedef struct _tagPoint
{
	float fX;
	float fY;

	_tagPoint operator + (const _tagPoint& _ptPos)
	{
		return _tagPoint(fX + _ptPos.fX, fY + _ptPos.fY);
	}

	_tagPoint()
	{}
	_tagPoint(float _fX, float _fY)
		: fX(_fX), fY(_fY)
	{}
} tPoint;

typedef struct _tagUIState
{
	bool bMouseOn;
	bool bLBtnClicked;
	bool bRBtnClicked;
} tUIState;

typedef unsigned short US;

typedef struct _tagStat
{
	US STR; // ��
	US DEX; // ��ø
	US LUK; // ��
	US INT; // ����
	_tagStat()
		: STR(0),
		DEX(0),
		LUK(0),
		INT(0) {}
}tStat;

typedef struct _tagColInfo // �浹ü�� ����
{
	COL_TYPE	eType;      // �浹ü�� ��� Ÿ��
	tPoint		ptPos;      // �浹ü�� ��ġ
	tPoint		ptOffset;   // �浹ü�� �ɼ� ���� �÷��̾��� �ȿ� �浹ü�� �ΰ� ������ ������ Ȱ��
	tPoint		ptSize;     // �浹ü�� ũ��
	_tagColInfo()  // �⺻ ������
		: eType(COL_TYPE::NONE)
		, ptPos(tPoint(0.f, 0.f))
		, ptOffset(tPoint(0.f, 0.f))
		, ptSize(tPoint(0.f, 0.f))
	{}
	_tagColInfo(COL_TYPE _eType, tPoint _ptPos, tPoint _ptOffset, tPoint _ptSize) // ������ �� �������ִ� ������
		: eType(_eType)
		, ptPos(_ptPos)
		, ptOffset(_ptOffset)
		, ptSize(_ptSize)
	{}
}tColInfo;