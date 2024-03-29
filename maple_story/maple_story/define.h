#pragma once

// 윈도우 사이즈 설정
#define WINSIZE_X 1200
#define WINSIZE_Y 800

//SINGLETONE 사용시 유의할 점: 생성자와 소멸자를 private으로 바꾸어 주어야 한다.  
#define SINGLETONE(type) public: \
							static type* GetInst() \
							{	\
								static type mgr; \
								return &mgr; \
							}

#define GRAVITY_ACCELERATE 2000
#define GRAVITY_JUMP 600 

#define DT CTimeMgr::GetInst()->DeltaTime()
#define GET_KEY(k,s) CKeyMgr::GetInst()->GetKeyState(k, s)

#define SAFE_DELETE(p) if(NULL != p) delete p; p = NULL;
#define SAFE_DELETE_ARR(p) if(NULL != p) delete[] p; p = NULL;

#define PLAYER_SIZE  70
#define MONSTER_SIZE 70
#define MAX_STR 255

enum class SCENE_TYPE
{
	LOGO,
	START,
	TESTSCENE,
	ANIM_TOOL,
	END,
};

enum class PLAYER_MOTION_TYPE
{
	STAND_LEFT,
	STAND_RIGHT,
	WALK_LEFT,
	WALK_RIGHT,
	JUMP_LEFT,
	JUMP_RIGHT,
	LIE_DOWN_FLAT, // 납작 엎드리다
	ATTACK1_LEFT,
	ATTACK1_RIGHT,
	//ATTACK1_FINISH_L,
	//ATTACK1_FINISH_R,
	END,
};

enum class MONSTER_MOTION_TYPE
{
	STAND_LEFT,
	ATTACKED_LEFT,

	END,
};

enum class COL_TYPE // 충돌체의 타입
{
	RECTANGLE, // 사각형
	CIRCLE,    // 원
	NONE,
};