#pragma once
class CObj;

class CLayer
{
private:
	list<CObj*>		m_listObj;

public:
	int update();
	void render(HDC _dc);

public:
	void AddObject(CObj* _pObj);
	void DeleteObjects();
	list<CObj*>& GetObjList() { return m_listObj; }

public:
	CLayer();
	~CLayer();
};

