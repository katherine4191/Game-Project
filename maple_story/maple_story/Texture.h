#pragma once
class CTexture
{
private:
	HBITMAP  m_hBitmap;
	HDC	     m_memDC;
	POINT	 m_ptSize; // texture size
	wstring  m_strKey; 
	wstring  m_strPath;

public:
	bool Load(const wstring& _strFullPath);
	HDC GetDC() { return m_memDC; }
	POINT GetTextureSize() { return m_ptSize; }

	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	const wstring& GetKey() { return m_strKey; }

	void SetPath(const wstring& _strPath) { m_strPath = _strPath; }
	const wstring& GetPath() { return m_strPath; }

public:
	CTexture();
	~CTexture();
};

