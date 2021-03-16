#pragma once

class CTexture;
class CAnimator;

class CAnimation
{
private:
	CAnimator*			m_pAnimator;
	CTexture*				m_pTex;		 // Animation이 참조하는 Texture

	WORD			m_wMaxFrame; // Animation의 최대 이미지 갯수
	WORD			m_wCurFrame; // 현재 재생하고 있는 이미지 인덱스

	tAnimFrame*		m_pFrame;
	float					m_fAccTime;
	bool					m_bRepeat;
	bool					m_bActive;
	bool					m_bAnimFinish_T; // update 위쪽에서 애니메이션 끝 도달을 판정하므로
	bool					m_bAnimFinish;
	wstring				m_strKey;

public:
	int update();
	void render(HDC _dc);

	void SetAnimator(CAnimator* _pOwner) { m_pAnimator = _pOwner; }
	void SetMaxFrame(int _iMaxFrame);
	void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }
	void SetCurFrame(WORD _wCurFrame) { m_wCurFrame = _wCurFrame; }
	void SetActive(bool _bActive) { m_bActive = _bActive; }
	void SetAnimKey(const wstring& _str) { m_strKey = _str; }

	CTexture* GetAnimTex() { return m_pTex; }
	WORD GetMaxFrame() { return m_wMaxFrame; }
	tAnimFrame* GetFrame() { return m_pFrame; }
	int GetCurFrame() { return m_wCurFrame; }
	const wstring& GetAnimKey() { return m_strKey; }

	bool IsAnimFinish() { return m_bAnimFinish; }
	void SetAnimbFinish(bool _bAnimFinish) { m_bAnimFinish = _bAnimFinish; }

public:
	void PlayAnimation(bool _bRepeat);

public:
	CAnimation();
	~CAnimation();

};

