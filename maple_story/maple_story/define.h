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

#define SAFE_DELETE(p) if(NULL != p) delete p; p = NULL;
#define SAFE_DELETE_ARR(p) if(NULL != p) delete[] p; p = NULL;

enum class SCENE_TYPE
{
	LOGO,
	START,
	TESTSCENE,
	ANIM_TOOL,
	END,
};