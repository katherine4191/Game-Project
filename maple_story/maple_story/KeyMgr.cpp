#include "pch.h"
#include "KeyMgr.h"

void CKeyMgr::init()
{
	m_mapKey.insert(make_pair('Q', KEY_STATE::NONE)); m_mapKey.insert(make_pair('A', KEY_STATE::NONE)); m_mapKey.insert(make_pair('Z', KEY_STATE::NONE));
	m_mapKey.insert(make_pair('W', KEY_STATE::NONE)); m_mapKey.insert(make_pair('S', KEY_STATE::NONE)); m_mapKey.insert(make_pair('X', KEY_STATE::NONE));
	m_mapKey.insert(make_pair('E', KEY_STATE::NONE)); m_mapKey.insert(make_pair('D', KEY_STATE::NONE)); m_mapKey.insert(make_pair('C', KEY_STATE::NONE));
	m_mapKey.insert(make_pair('R', KEY_STATE::NONE)); m_mapKey.insert(make_pair('F', KEY_STATE::NONE)); m_mapKey.insert(make_pair('V', KEY_STATE::NONE));
	m_mapKey.insert(make_pair('T', KEY_STATE::NONE)); m_mapKey.insert(make_pair('G', KEY_STATE::NONE)); m_mapKey.insert(make_pair('B', KEY_STATE::NONE));
	m_mapKey.insert(make_pair('Y', KEY_STATE::NONE)); m_mapKey.insert(make_pair('H', KEY_STATE::NONE)); m_mapKey.insert(make_pair('N', KEY_STATE::NONE));
	m_mapKey.insert(make_pair('U', KEY_STATE::NONE)); m_mapKey.insert(make_pair('J', KEY_STATE::NONE)); m_mapKey.insert(make_pair('M', KEY_STATE::NONE));
	m_mapKey.insert(make_pair('I', KEY_STATE::NONE)); m_mapKey.insert(make_pair('K', KEY_STATE::NONE));
	m_mapKey.insert(make_pair('O', KEY_STATE::NONE)); m_mapKey.insert(make_pair('L', KEY_STATE::NONE));
	m_mapKey.insert(make_pair('P', KEY_STATE::NONE));

	m_mapKey.insert(make_pair(VK_LEFT, KEY_STATE::NONE));  m_mapKey.insert(make_pair(VK_SPACE, KEY_STATE::NONE));
	m_mapKey.insert(make_pair(VK_RIGHT, KEY_STATE::NONE));  m_mapKey.insert(make_pair(VK_ESCAPE, KEY_STATE::NONE));
	m_mapKey.insert(make_pair(VK_DOWN, KEY_STATE::NONE));  m_mapKey.insert(make_pair(VK_RETURN, KEY_STATE::NONE));
	m_mapKey.insert(make_pair(VK_UP, KEY_STATE::NONE));  m_mapKey.insert(make_pair(VK_TAB, KEY_STATE::NONE));
	m_mapKey.insert(make_pair(VK_LBUTTON, KEY_STATE::NONE));
	m_mapKey.insert(make_pair(VK_RBUTTON, KEY_STATE::NONE));
}

int CKeyMgr::update()
{
	map<WORD, KEY_STATE>::iterator iter = m_mapKey.begin();

	if (!g_bActive)
	{
		for (; iter != m_mapKey.end(); ++iter)
			iter->second = KEY_STATE::NONE;
		return 0;
	}

	for (; iter != m_mapKey.end(); ++iter)
	{
		if (GetAsyncKeyState(iter->first) & 0x8000) // 현재 키가 눌려있다.
		{
			if (iter->second == KEY_STATE::NONE) // 이전에 눌린 적이 없다면
				iter->second = KEY_STATE::PRESS; // 이제 막 누른 상태
			else 				
				iter->second = KEY_STATE::HOLD; // 계속 누르고 있는 상태

		}
		else // 현재 키가 눌려있지 않다.
		{
			if (iter->second != KEY_STATE::NONE && iter->second != KEY_STATE::AWAY) // 이전에 눌려있었다.
				iter->second = KEY_STATE::AWAY;
			else
				iter->second = KEY_STATE::NONE;
		}
	}
    return 0;
}

KEY_STATE CKeyMgr::GetKeyState(DWORD _Key)
{
	map<WORD, KEY_STATE>::iterator iter = m_mapKey.find(_Key);

	if (iter == m_mapKey.end())
		return KEY_STATE::NONE;

	return iter->second;
}

bool CKeyMgr::GetKeyState(DWORD _key, KEY_STATE _eState)
{
	map<WORD, KEY_STATE>::iterator iter = m_mapKey.find(_key);

	if (iter == m_mapKey.end())
		return false;

	return (_eState == iter->second);
}

CKeyMgr::~CKeyMgr()
{
}
