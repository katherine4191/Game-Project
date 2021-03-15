#include "pch.h"
#include "Animator.h"

#include "Animation.h"
#include "ResMgr.h"
#include "pathmgr.h"
#include "texture.h"

CAnimator::CAnimator()
	: m_pOwner(NULL)
	, m_pCurAnim(NULL)
{
}

CAnimator::~CAnimator()
{
}

int CAnimator::update()
{
	if (NULL != m_pCurAnim)
		m_pCurAnim->update();
	return 0;
}

void CAnimator::render(HDC _dc)
{
	if (NULL != m_pCurAnim)
		m_pCurAnim->render(_dc);
}


bool CAnimator::AddAnimation(const wstring& _strAnimKey, const wstring& _strTexKey, int _iMaxFrame)
{
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(_strTexKey);

	if (NULL == pTex)
		return false;

	CAnimation* pAnim = new CAnimation;
	pAnim->SetAnimator(this);
	pAnim->SetMaxFrame(_iMaxFrame);
	pAnim->SetTexture(pTex);

	m_pCurAnim = pAnim;

	m_mapAnim.insert(make_pair(_strAnimKey, pAnim));
	pAnim->SetAnimKey(_strAnimKey);

	return true;
}

void CAnimator::Clear()
{
	Safe_Delete_Map(m_mapAnim);
}

bool CAnimator::LoadAnimation(const wstring& _strAnimPath)
{
	wstring strPath = CPathMgr::GetResourcesPath();
	strPath += _strAnimPath;

	FILE* pFile = NULL;
	_wfopen_s(&pFile, strPath.c_str(), L"rb");

	if (NULL == pFile)
	{
		// 무언가 출력해주기
		return false;
	}

	// Texture  의 키값과 경로값 읽기
	wchar_t szKey[MAX_STR] = L"";
	wchar_t szPath[MAX_STR] = L"";

	LoadWString(szKey, pFile);
	LoadWString(szPath, pFile);

	// Animation 참조 텍스쳐 설정
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(szKey, szPath);

	if (NULL == pTex)
	{
		fclose(pFile);
		return false;
	}

	// Animation 이름 읽기
	LoadWString(szKey, pFile);

	// Animation 의 최대 프레임 수 읽기		
	int iMaxFrame = 0;
	fread(&iMaxFrame, sizeof(int), 1, pFile);

	// Animator 에 Animation 추가하기
	AddAnimation(szKey, pTex->GetKey(), iMaxFrame);

	// m_pCurAnim 이 방금추가한 Animation 을 가리키고 있다. 
	m_pCurAnim->SetTexture(pTex);
	m_pCurAnim->SetActive(false);

	// Animation Frame 정보 읽기
	tAnimFrame* pFrame = m_pCurAnim->GetFrame();
	fread(pFrame, sizeof(tAnimFrame), iMaxFrame, pFile);

	fclose(pFile);

	return true;
}

void CAnimator::PlayAnimation(const wstring& _strAnimName, bool _bRpeat)
{
	map<wstring, CAnimation*>::iterator map_iter = m_mapAnim.find(_strAnimName);
	if (map_iter == m_mapAnim.end())
		return;

	// strAinimName에 해당하는 애니메이션을 얻어와서 현재 애니메이션으로 지정하고
	m_pCurAnim = map_iter->second;

	if (NULL != m_pCurAnim) //현재 애니메이션을 재생한다.
		m_pCurAnim->PlayAnimation(_bRpeat);
}


bool CAnimator::IsAnimFinish(const wstring& _strAnimName)
{
	map<wstring, CAnimation*>::iterator map_iter = m_mapAnim.find(_strAnimName);
	if (map_iter == m_mapAnim.end())
		return false;
	return map_iter->second->IsAnimFinish();
}

void CAnimator::SetAnimbFinish(const wstring& _strAnimName, bool _bFinish)
{
	map<wstring, CAnimation*>::iterator map_iter = m_mapAnim.find(_strAnimName);
	if (map_iter == m_mapAnim.end())
		return;
	return map_iter->second->SetAnimbFinish(_bFinish);
}