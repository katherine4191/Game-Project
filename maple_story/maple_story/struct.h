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