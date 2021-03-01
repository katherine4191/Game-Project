#pragma once
class CObj
{
protected:
	wstring m_strObjTag;
	tPoint	m_ptPos;

public:
	virtual void init() {};
	virtual int update() = 0;
	virtual void render(HDC _dc) = 0;

	void SetPos(tPoint _pt) { m_ptPos = _pt; }
	tPoint GetPos() { return m_ptPos; }

	void SetTag(const wstring& _strTag) { m_strObjTag = _strTag; }
	const wstring& GetTag() { return m_strObjTag; }

	//CAnimator* GetAnimator();

	//virtual bool IsCollision() { return false; }

public:
	CObj();
	CObj(wstring _strObjTag, tPoint _ptPos);
	virtual ~CObj();
};

