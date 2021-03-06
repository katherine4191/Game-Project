#include "pch.h"
#include "Texture.h"

#include "Core.h"

CTexture::CTexture()
{
}

CTexture::~CTexture()
{
	DeleteObject(m_hBitmap);
	DeleteDC(m_memDC);
}

bool CTexture::Load(const wstring& _strFullPath)
{
	m_hBitmap = (HBITMAP)LoadImage(NULL, _strFullPath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);

	if (NULL == m_hBitmap) // Texture Loading Fail
	{
		return false;
	}

	m_memDC = CreateCompatibleDC(CCore::GetInst()->GetDC());
	HBITMAP oldBit = (HBITMAP)SelectObject(m_memDC, m_hBitmap);
	DeleteObject(oldBit);

	BITMAP bit;
	GetObject(m_hBitmap, sizeof(BITMAP), &bit);
	m_ptSize.x = bit.bmWidth;	m_ptSize.y = bit.bmHeight;

	return true;
}