#pragma once
// pch.h: �̸� �����ϵ� ��� �����Դϴ�.
// �Ʒ� ������ ������ �� ���� �����ϵǾ�����, ���� ���忡 ���� ���� ������ ����մϴ�.
// ���⿡ ���� ������Ʈ�� ������ �߰����� ������. �׷��� ������ ���ϵ˴ϴ�.




#ifndef PCH_H
#define PCH_H

// ���⿡ �̸� �������Ϸ��� ��� �߰�
#include "framework.h"

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h> // HWND g_hWnd;�� ���ؼ�

#include <wingdi.h>

#include <functional>

#include <iostream> // wstring
#include <map>
#include <list>
#include <vector>

using namespace std;
#include "global.h"
#endif //PCH_H
