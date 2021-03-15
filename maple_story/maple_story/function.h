#pragma once
template<typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	map<T1, T2>::iterator iter = _map.begin();
	for (; iter != _map.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	_map.clear();
}

template<typename T1>
void Safe_Delete_list(list<T1>& _list)
{
	list<T1>::iterator iter = _list.begin();
	for (; iter != _list.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	_list.clear();
}

void LoadWString(wchar_t* _pStr, FILE* _pFile);