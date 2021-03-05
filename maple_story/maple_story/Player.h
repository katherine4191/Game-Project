#pragma once
class CPlayer
{
private:
	tStat					m_tStat; // STR(Èû),DEX(¹ÎÃ¸),LUK(¿î),INT(Áö´É)
	int						m_iJumpStack;
	int						m_iMaxJumpStack;

	/*CAnimator* m_pAnimator;*/

	PLAYER_MOTION_TYPE      m_ePMotionType;
	bool                    m_arrMotionProgress[(int)PLAYER_MOTION_TYPE::END];

public:
	virtual void init();
	virtual int update();
	virtual void render(HDC _dc);

	const tStat& GetStat() { return m_tStat; }
	void SetStat(const tStat& _tStat) { m_tStat = _tStat; }
	void AfterLand(void);
	//const CAttackBox& GetAttackBox() { return m_AttackCollision; } 

private:
	void ControlMotionRender();

public:
	//CPlayer();
	CPlayer(wstring _strObjTag, tPoint _ptPos);
	virtual ~CPlayer();
};

