#pragma once
#include "Scene.h"

class TestScene :
	public CScene
{
public:
	virtual void init();
	virtual int update();
public:
	TestScene();
	virtual ~TestScene();
};