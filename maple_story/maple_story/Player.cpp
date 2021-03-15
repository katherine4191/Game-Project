#include "pch.h"
#include "Player.h"

#include "KeyMgr.h"
#include "SceneMgr.h"
#include "TimeMgr.h"

#include "CollisionGravityObj.h"

CPlayer::CPlayer(wstring _strObjTag, tPoint _ptPos)
	:CCollisionGravityObj(_strObjTag, _ptPos),
	m_iJumpStack(3), m_iMaxJumpStack(3), m_ePMotionType(PLAYER_MOTION_TYPE::STAND_RIGHT)
{
	memset(&m_tStat, 0, sizeof(tStat));
	m_ptPos = tPoint(WINSIZE_X / 2, WINSIZE_Y - PLAYER_SIZE);
	//m_pAnimator = GetAnimator();
}

CPlayer::~CPlayer()
{
}

void CPlayer::init()
{
	// Animation 로드
	/*m_pAnimator->LoadAnimation(L"Animation\\PA_Walk_Left.anim");
	m_pAnimator->LoadAnimation(L"Animation\\PA_Walk_Right.anim");
	m_pAnimator->LoadAnimation(L"Animation\\PA_Jump_Right.anim");
	m_pAnimator->LoadAnimation(L"Animation\\PA_Jump_Left.anim");
	m_pAnimator->LoadAnimation(L"Animation\\PA_LieDown_Left.anim");
	m_pAnimator->LoadAnimation(L"Animation\\PA_Attack1_Left.anim");
	m_pAnimator->LoadAnimation(L"Animation\\PA_Attack1_Right.anim");

	m_pAnimator->LoadAnimation(L"Animation\\PA_Stand_Left.anim");
	m_pAnimator->LoadAnimation(L"Animation\\PA_Stand_Right.anim");*/

	// Collision 정보 셋팅
	m_Collision.SetCollisionInfo(tColInfo(COL_TYPE::CIRCLE, m_ptPos, tPoint(-3.f, 0.f), tPoint(66.f, 66.f)));
	m_AttackCollision.SetCollisionInfo(tColInfo(COL_TYPE::RECTANGLE, m_ptPos, tPoint(35.f, 0.f), tPoint(30.f, 30.f)));

	//functional
	m_vecPostGround.push_back(bind(&CPlayer::AfterLand, this));
}

int CPlayer::update()
{
	// 땅위에 있는지 아닌지 체크
	CheckGround();

	// 점프를 누르면
	if (GET_KEY(VK_SPACE, KEY_STATE::PRESS) && m_iJumpStack != 0)
	{
		m_iJumpStack -= 1;
		m_bGround = false;
		m_iVerticalSpeed = -GRAVITY_JUMP;

		if (m_ePMotionType == PLAYER_MOTION_TYPE::STAND_RIGHT)
			m_ePMotionType = PLAYER_MOTION_TYPE::JUMP_RIGHT;

		else if (m_ePMotionType == PLAYER_MOTION_TYPE::STAND_LEFT)
			m_ePMotionType = PLAYER_MOTION_TYPE::JUMP_LEFT;

		m_arrMotionProgress[(int)m_ePMotionType] = true;
	}

	// 공중에 있다면(m_bGround == false)
	if (!m_bGround)
	{
		// 중력가속도에 의한 낙하
		m_ptPos.fY += m_iVerticalSpeed * DT;
		m_iVerticalSpeed += GRAVITY_ACCELERATE * DT;
		// 공중에 있다는 말은 이미 스페이스가 눌렸다는 전제하이므로.
		if (GET_KEY(VK_LEFT, KEY_STATE::HOLD))
			m_ePMotionType = PLAYER_MOTION_TYPE::JUMP_LEFT;
		if (GET_KEY(VK_RIGHT, KEY_STATE::HOLD))
			m_ePMotionType = PLAYER_MOTION_TYPE::JUMP_RIGHT;

		m_arrMotionProgress[(int)m_ePMotionType] = true;
	}

	if (m_ptPos.fY < WINSIZE_Y - (PLAYER_SIZE * 1)) {
		m_ptPos.fY += m_iVerticalSpeed * DT;
	}
	else
	{
		m_ptPos.fY <= WINSIZE_Y - (PLAYER_SIZE * 2);
		m_iVerticalSpeed = 100;
	}
	if (GET_KEY(VK_LEFT, KEY_STATE::PRESS))
	{
		m_ePMotionType = PLAYER_MOTION_TYPE::WALK_LEFT;
		m_arrMotionProgress[(int)m_ePMotionType] = true;
	}

	if (GET_KEY(VK_LEFT, KEY_STATE::HOLD))
		m_ptPos.fX -= m_iHorizonSpeed * DT;

	if (GET_KEY(VK_LEFT, KEY_STATE::AWAY))
	{
		if (m_ePMotionType == PLAYER_MOTION_TYPE::WALK_LEFT) {
			m_ePMotionType = PLAYER_MOTION_TYPE::STAND_LEFT;
			m_arrMotionProgress[(int)m_ePMotionType] = true;
		}
	}

	if (GET_KEY(VK_RIGHT, KEY_STATE::PRESS))
	{
		m_ePMotionType = PLAYER_MOTION_TYPE::WALK_RIGHT;
		m_arrMotionProgress[(int)m_ePMotionType] = true;
	}
	if (GET_KEY(VK_RIGHT, KEY_STATE::HOLD))
		m_ptPos.fX += m_iHorizonSpeed * DT;

	if (GET_KEY(VK_RIGHT, KEY_STATE::AWAY))
	{
		if (m_ePMotionType == PLAYER_MOTION_TYPE::WALK_RIGHT) {
			m_ePMotionType = PLAYER_MOTION_TYPE::STAND_RIGHT;
			m_arrMotionProgress[(int)m_ePMotionType] = true;
		}
	}

	if (GET_KEY(VK_DOWN, KEY_STATE::HOLD))
	{
		m_ptPos.fY += m_iHorizonSpeed * DT;
		m_ePMotionType = PLAYER_MOTION_TYPE::LIE_DOWN_FLAT;
		m_arrMotionProgress[(int)m_ePMotionType] = true;
	}

	// 공 격 // 
	if (GET_KEY('A', KEY_STATE::PRESS))
	{
		if (m_ePMotionType == PLAYER_MOTION_TYPE::STAND_LEFT || m_ePMotionType == PLAYER_MOTION_TYPE::WALK_LEFT)
			m_ePMotionType = PLAYER_MOTION_TYPE::ATTACK1_LEFT;
		else if (m_ePMotionType == PLAYER_MOTION_TYPE::STAND_RIGHT || m_ePMotionType == PLAYER_MOTION_TYPE::WALK_RIGHT)
			m_ePMotionType = PLAYER_MOTION_TYPE::ATTACK1_RIGHT;

		m_arrMotionProgress[(int)m_ePMotionType] = true;
	}
	//// 공격 후 원래 상태로 돌려놓기
	//if (m_pAnimator->IsAnimFinish(L"PA_Attack1_Left"))
	//{
	//	m_ePMotionType = PLAYER_MOTION_TYPE::STAND_LEFT;
	//	m_arrMotionProgress[(int)m_ePMotionType] = true;
	//	m_pAnimator->SetbAnimFinish(L"PA_Attack1_Left", false);
	//}

	//if (m_pAnimator->IsAnimFinish(L"PA_Attack1_Right"))
	//{
	//	m_ePMotionType = PLAYER_MOTION_TYPE::STAND_RIGHT;
	//	m_arrMotionProgress[(int)m_ePMotionType] = true;
	//	m_pAnimator->SetbAnimFinish(L"PA_Attack1_Right", false);
	//}

	//m_pAnimator->update();
	CCollisionObj::update();
	return 0;
}

void CPlayer::render(HDC _dc)
{
	ControlMotionRender();
	//m_pAnimator->render(_dc);
	CCollisionObj::render(_dc);
}


void CPlayer::AfterLand(void)
{
	m_iJumpStack = m_iMaxJumpStack;
	m_ptPos.fY = WINSIZE_Y - (PLAYER_SIZE * 1);

	if (PLAYER_MOTION_TYPE::JUMP_LEFT == m_ePMotionType)
	{
		if (GET_KEY(VK_LEFT, KEY_STATE::HOLD))
			m_ePMotionType = PLAYER_MOTION_TYPE::WALK_LEFT;
		else
			m_ePMotionType = PLAYER_MOTION_TYPE::STAND_LEFT;
	}

	else if (PLAYER_MOTION_TYPE::JUMP_RIGHT == m_ePMotionType)
	{
		if (GET_KEY(VK_RIGHT, KEY_STATE::HOLD))
			m_ePMotionType = PLAYER_MOTION_TYPE::WALK_RIGHT;
		else
			m_ePMotionType = PLAYER_MOTION_TYPE::STAND_RIGHT;
	}
	m_arrMotionProgress[(int)m_ePMotionType] = true;
}

void CPlayer::ControlMotionRender()
{
	int arrIdx = (int)PLAYER_MOTION_TYPE::END;
	for (int i = 0; i < arrIdx; ++i)
	{
		if (m_arrMotionProgress[i])
		{
			//if (i == (int)PLAYER_MOTION_TYPE::STAND_LEFT)
			//	m_pAnimator->PlayAnimation(L"PA_Stand_Left", true);
			//else if (i == (int)PLAYER_MOTION_TYPE::STAND_RIGHT)
			//	m_pAnimator->PlayAnimation(L"PA_Stand_Right", true);
			//else if (i == (int)PLAYER_MOTION_TYPE::WALK_LEFT)
			//	m_pAnimator->PlayAnimation(L"PA_Walk_Left", true);
			//else if (i == (int)PLAYER_MOTION_TYPE::WALK_RIGHT)
			//	m_pAnimator->PlayAnimation(L"PA_Walk_Right", true);
			//else if (i == (int)PLAYER_MOTION_TYPE::LIE_DOWN_FLAT)
			//	m_pAnimator->PlayAnimation(L"PA_LieDown_Left", true);
			//else if (i == (int)PLAYER_MOTION_TYPE::JUMP_RIGHT)
			//	m_pAnimator->PlayAnimation(L"PA_Jump_Right", true);
			//else if (i == (int)PLAYER_MOTION_TYPE::JUMP_LEFT)
			//	m_pAnimator->PlayAnimation(L"PA_Jump_Left", true);
			//else if (i == (int)PLAYER_MOTION_TYPE::ATTACK1_LEFT) {
			//	m_pAnimator->PlayAnimation(L"PA_Attack1_Left", false);
			//}
			//else if (i == (int)PLAYER_MOTION_TYPE::ATTACK1_RIGHT) {
			//	m_pAnimator->PlayAnimation(L"PA_Attack1_Right", false);
			//	//m_pAnimator->SetAnimFrmCollsionOn();
			//}

			// 여기에 들어왔다는 건 true라는 것이다. 
			m_arrMotionProgress[i] = 0;
		}
	}
}


