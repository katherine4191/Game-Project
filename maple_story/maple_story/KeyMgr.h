#pragma once

enum class KEY_STATE
{
	NONE,
	PRESS,
	HOLD,
	AWAY,
};

class CKeyMgr
{
	SINGLETONE(CKeyMgr)

private:
	map<WORD, KEY_STATE> m_mapKey;

public:
	void init();
	int update();

public:
	KEY_STATE GetKeyState(DWORD _Key);
	bool GetKeyState(DWORD _key, KEY_STATE _eState);

private:
	CKeyMgr();
	~CKeyMgr();
};
