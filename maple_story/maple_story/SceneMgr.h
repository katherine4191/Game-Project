#pragma once
class CScene;
class CObj;

class CSceneMgr
{
	SINGLETONE(CSceneMgr)

private:
	CScene* m_pCurScene;
	CScene* m_pPrevScene;
	CScene* m_arrScene[(int)SCENE_TYPE::END];

public:	
	void init();
	int update();
	void render(HDC _dc);

	CScene* GetCurScene() { return m_pCurScene; }
	void ChangeScene(SCENE_TYPE _eNextScene);
	void AddObject(const wstring& _strLayerName, CObj* _pObj);
	CObj* FindObject(const wstring& _strTag);
	CObj* FindObject(const wstring& _strLayerName, const wstring& _strTag);

private:
	CSceneMgr();
	~CSceneMgr();
};

