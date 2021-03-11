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

	// ��輱�� �浹ü�� ������ �� �� �ֵ��� ���� ����
	m_Border.SetPos(m_ColInfo.ptPos + m_ColInfo.ptOffset);
	m_Border.SetSize(m_ColInfo.ptSize);
}

int CCollision::update() // �浹ü�� �ڽ��� ������ CCollsionobj�� ���󰡾��Ѵ�.
{
	m_ColInfo.ptPos = m_pOwner->GetPos();

	// �浹ü ��ġ���� ī�޶� ���� ��ġ�� ������ ��ǥ�� ��輱 ��ü�� �����Ѵ�.
	tPoint ptBorderPos = m_ColInfo.ptPos + m_ColInfo.ptOffset; // �浹ü�� ��ġ
	ptBorderPos = CCamera::GetInst()->GetStdCamPos(ptBorderPos); // �浹ü ��ġ�� ī�޶� �������� �ٲپ
	m_Border.SetPos(ptBorderPos); // �浹ü�� ǥ�����ִ� ��輱 ��ġ�� �����Ѵ�.
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