#include "pch.h"
#include "Animation.h"

#include "TimeMgr.h"
#include "Texture.h"

#include "Obj.h"

CAnimation::CAnimation()
	: m_pTex(NULL)
	, m_wMaxFrame(0)
	, m_wCurFrame(0)
	, m_pFrame(NULL)
	, m_fAccTime(0.f)
	, m_bRepeat(false)
	, m_bActive(true)
	, m_bAnimFinish(false)
{
}

CAnimation::~CAnimation()
{
	SAFE_DELETE_ARR(m_pFrame);
}

int CAnimation::update()
{
	if (!m_bActive) // 아예 재생도 안했을 때나 재생하고 나서 멈추었을 때
	{
		return 0;
	}

	// m_Active = true 일때
	m_bAnimFinish = false;

	m_fAccTime += DT;
	if (m_fAccTime >= m_pFrame[m_wCurFrame].m_fTime) // 시간이 다 되면
	{
		// 1번만 재생하는 애니메이션이고 마지막 장면에 도달하였을 때 처리해주는 부분
		if (!m_bRepeat && m_wCurFrame == m_wMaxFrame - 1)
		{
			m_bActive = false;
			m_bAnimFinish = true;
			return 0;
		}
		else
			++m_wCurFrame; // 그 다음 프레임으로 넘어간다.

		if (m_wCurFrame >= m_wMaxFrame)
		{
			if (m_bRepeat)
				m_wCurFrame = 0;
		}
		m_fAccTime = 0.f;
	}

	return 0;
}

void CAnimation::render(HDC _dc)
{


}

void CAnimation::SetMaxFrame(int _iMaxFrame)
{
	if (m_wMaxFrame == _iMaxFrame)
		return;

	m_wMaxFrame = _iMaxFrame;

	if (NULL != m_pFrame)
		delete[] m_pFrame;

	m_pFrame = new tAnimFrame[m_wMaxFrame];
}

void CAnimation::PlayAnimation(bool _bRepeat)
{
	m_fAccTime = 0.f;
	m_wCurFrame = 0;
	m_bRepeat = _bRepeat;
	m_bActive = true;
	// 이렇게 초기화해주면 CAnimation::update()가 돌아가면서 알아서 화면에 출력해준다.
}

