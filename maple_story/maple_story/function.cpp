#include "pch.h"

void LoadWString(wchar_t* _pStr, FILE* _pFile)
{
	unsigned char c = 0;
	fread(&c, 1, 1, _pFile);
	fread(_pStr, sizeof(wchar_t), c, _pFile);
}
