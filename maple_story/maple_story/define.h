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

enum class SCENE_TYPE
{
	LOGO,
	START,
	TESTSCENE,
	ANIM_TOOL,
	END,
};