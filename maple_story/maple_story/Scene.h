#pragma once

class CLayer;
class CObj;

typedef struct _tagLayerInfo
{
	int		iIdx;
	CLayer* pLayer;
} tLayerInfo;

class CScene
{
private:
	int										m_iNextIdx;
	map<wstring, tLayerInfo>	m_mapLayer;
	map<int, tLayerInfo>			m_mapIdxLayer;

public:
	virtual void init() = 0;
	virtual int update();
	virtual void render(HDC);

	void AddLayer(const wstring& _strLayerName);
	bool AddObject(const wstring& _strLayerName, CObj* _pObj);
	bool DeleteObjects(const wstring& _strLayerName);
	CObj* FindObject(const wstring& _strTag);
	CObj* FindObject(const wstring& _strLayerName, const wstring& _strTag);
	
	int GetLayerIndex(const wstring& _strLayerName);
	CLayer* FindLayer(const wstring& _strLayerName);
	CLayer* FindLayer(int _iIdx);

public:
	CScene();
	virtual ~CScene();
};

