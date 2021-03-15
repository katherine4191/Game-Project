#pragma once

class CTexture;


class CAnimation
{
private:

	CTexture*				m_pTex;		 // Animation�� �����ϴ� Texture

	WORD			m_wMaxFrame; // Animation�� �ִ� �̹��� ����
	WORD			m_wCurFrame; // ���� ����ϰ� �ִ� �̹��� �ε���

	tAnimFrame*		m_pFrame;
	float					m_fAccTime;
	bool					m_bRepeat;
	bool					m_bActive;
	bool					m_bAnimFinish_T; // update ���ʿ��� �ִϸ��̼� �� ������ �����ϹǷ�
	bool					m_bAnimFinish;
	wstring				m_strKey;

public:
	int update();
	void render(HDC _dc);


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

public:
	void PlayAnimation(bool _bRepeat);

public:
	CAnimation();
	~CAnimation();

};

