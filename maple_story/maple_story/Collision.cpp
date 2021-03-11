#include "pch.h"
#include "Collision.h"

#include "CollisionObj.h"
#include "Camera.h"

WORD CCollision::g_iNextID = 0;

CCollision::CCollision(CCollisionObj* _pOwner)
	: m_pOwner(_pOwner)
{
	m_iColID = g_iNextID++;
	m_Border.SetColor(RGB(255, 0, 0));
	m_Border.SetPenWidth(1);
	m_Border.SetPos(m_ColInfo.ptPos + m_ColInfo.ptOffset);
	m_Border.SetSize(m_ColInfo.ptSize);
}

CCollision::~CCollision()
{
}

void CCollision::SetCollisionInfo(const tColInfo& _info)
{
	m_ColInfo = _info;

	// 경계선이 충돌체의 정보를 알 수 있도록 같이 수정
	m_Border.SetPos(m_ColInfo.ptPos + m_ColInfo.ptOffset);
	m_Border.SetSize(m_ColInfo.ptSize);
}

int CCollision::update() // 충돌체는 자신을 소유한 CCollsionobj을 따라가야한다.
{
	m_ColInfo.ptPos = m_pOwner->GetPos();

	// 충돌체 위치에서 카메라 기준 위치로 변경한 좌표를 경계선 객체에 셋팅한다.
	tPoint ptBorderPos = m_ColInfo.ptPos + m_ColInfo.ptOffset; // 충돌체의 위치
	ptBorderPos = CCamera::GetInst()->GetStdCamPos(ptBorderPos); // 충돌체 위치를 카메라 기준으로 바꾸어서
	m_Border.SetPos(ptBorderPos); // 충돌체를 표시해주는 경계선 위치를 설정한다.
	return 0;
}

void CCollision::render(HDC _dc)
{
	if (this->m_ColInfo.eType == COL_TYPE::CIRCLE)
		m_Border.CircleRender(_dc);
	else if (this->m_ColInfo.eType == COL_TYPE::RECTANGLE)
		m_Border.render(_dc);
}

void CCollision::OnCollisionEnter(CCollision* _pOther)
{
	m_pOwner->OnCollisionEnter();
}

void CCollision::OnCollision(CCollision* _pOther)
{
	m_pOwner->OnCollision();
}

void CCollision::OnCollisionExit(CCollision* _pOther)
{
	m_pOwner->OnCollisionExit();
}