#pragma once

// ������ ������ ����
#define WINSIZE_X 1200
#define WINSIZE_Y 800

//SINGLETONE ���� ������ ��: �����ڿ� �Ҹ��ڸ� private���� �ٲپ� �־�� �Ѵ�.  
#define SINGLETONE(type) public: \
							static type* GetInst() \
							{	\
								static type mgr; \
								return &mgr; \
							}

#define SAFE_DELETE(p) if(NULL != p) delete p; p = NULL;
#define SAFE_DELETE_ARR(p) if(NULL != p) delete[] p; p = NULL;

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
	LIE_DOWN_FLAT, // ���� ���帮��
	ATTACK1_LEFT,
	ATTACK1_RIGHT,
	//ATTACK1_FINISH_L,
	//ATTACK1_FINISH_R,
	END,
};