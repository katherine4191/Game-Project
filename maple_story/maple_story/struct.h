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

typedef struct _tagInfo
{
	//RACE_TYPE eType;
	US CurHP;
	US MaxHP;
	US CurMP;
	US MaxMP;
	US Level;
	US Attack;
	US Defence;
	unsigned int CurExp;
	unsigned int MaxExp;
	_tagInfo()
		: CurHP(0), MaxHP(0), CurMP(0), MaxMP(0), Level(0), Attack(0), Defence(0), CurExp(0), MaxExp(0) {}

	_tagInfo(US _CurHP, US _MaxHP, US _CurMP, US _MaxMP, US _Level, US _Attack, US _Defence, unsigned int _CurExp, unsigned int MaxExp)
		: CurHP(_CurHP), MaxHP(_MaxHP), CurMP(_CurMP), MaxMP(_MaxMP), Level(_Level), Attack(_Attack), Defence(_Defence),
		CurExp(_CurExp), MaxExp(MaxExp) {}
}tInfo;

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