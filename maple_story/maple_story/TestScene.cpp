#include "pch.h"
#include "TestScene.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

void TestScene::init()
{
	AddLayer(L"Player");
	AddLayer(L"Monster");
	AddLayer(L"Border");
}

int TestScene::update()
{
	CScene::update();
	return 0;
}