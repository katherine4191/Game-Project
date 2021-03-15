#pragma once

class CAnimation;
class CObj;

class CAnimator
{
private:
	CObj*									m_pOwner;
	map<wstring, CAnimation*>	m_mapAnim;
	CAnimation*							m_pCurAnim;

public:
	int update();
	void render(HDC _dc);

public:
	void SetOwner(CObj* _pOwner) { m_pOwner = _pOwner; }
	CObj* GetOwner() { return m_pOwner; }
	bool AddAnimation(const wstring& _strAnimKey, const wstring& _strTex, int _iMaxFrame);
	CAnimation* GetCurAnimation() { return m_pCurAnim; }
	void Clear();
	bool LoadAnimation(const wstring& _strAnimPath);
	//void PlayAnimation(bool _bRpeat);

	void PlayAnimation(const wstring& _strAnimName, bool _bRpeat);
	bool IsAnimFinish(const wstring& _strAnimName);
	void SetAnimbFinish(const wstring& _strAnimName, bool _bFinish);
public:
	CAnimator();
	~CAnimator();
};

