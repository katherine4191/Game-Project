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
	if (!m_bActive) // �ƿ� ����� ������ ���� ����ϰ� ���� ���߾��� ��
	{
		return 0;
	}

	// m_Active = true �϶�
	m_bAnimFinish = false;

	m_fAccTime += DT;
	if (m_fAccTime >= m_pFrame[m_wCurFrame].m_fTime) // �ð��� �� �Ǹ�
	{
		// 1���� ����ϴ� �ִϸ��̼��̰� ������ ��鿡 �����Ͽ��� �� ó�����ִ� �κ�
		if (!m_bRepeat && m_wCurFrame == m_wMaxFrame - 1)
		{
			m_bActive = false;
			m_bAnimFinish = true;
			return 0;
		}
		else
			++m_wCurFrame; // �� ���� ���������� �Ѿ��.

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
	// �̷��� �ʱ�ȭ���ָ� CAnimation::update()�� ���ư��鼭 �˾Ƽ� ȭ�鿡 ������ش�.
}

