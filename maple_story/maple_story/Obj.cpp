#include "pch.h"
#include "Obj.h"

#include "animator.h"

CObj::CObj()
{
}

CObj::CObj(wstring _strObjTag, tPoint _ptPos) 
	: m_ptPos(tPoint(WINSIZE_X / 2, WINSIZE_Y / 2))
{
	m_strObjTag = _strObjTag;
	m_ptPos = _ptPos;
}

CObj::~CObj()
{
}

CAnimator* CObj::GetAnimator()
{
	CAnimator* pAnimator = new CAnimator;
	pAnimator->SetOwner(this);
	return pAnimator;
}