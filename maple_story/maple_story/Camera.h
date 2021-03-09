#pragma once
class CCamera
{
	SINGLETONE(CCamera)

private:
	tPoint		m_ptFocus;
	tPoint		m_ptDiff;

public:
	void init();
	int update();

	tPoint GetStdCamPos(tPoint _ptRealPos); // 게임 상의 실제 위치를 카메라 기준으로 보정한 위치를 반환
	tPoint GetCamFocus()  {	return m_ptFocus;	} // 카메라가 현재 바라보고 있는 위치 반환
	void SetCamFocus(tPoint _ptPos) { m_ptFocus = _ptPos; } // 카메라 초첨 설정
	POINT GetMousePos(); // 마우스 위치를 얻어와 카메라 기준으로 변경

public:
	CCamera();
	~CCamera();
};

