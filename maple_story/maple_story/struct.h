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

typedef unsigned short US;

typedef struct _tagStat
{
	US STR; // Èû
	US DEX; // ¹ÎÃ¸
	US LUK; // ¿î
	US INT; // Áö´É
	_tagStat()
		: STR(0),
		DEX(0),
		LUK(0),
		INT(0) {}
}tStat;