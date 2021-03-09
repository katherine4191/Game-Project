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

	tPoint GetStdCamPos(tPoint _ptRealPos); // ���� ���� ���� ��ġ�� ī�޶� �������� ������ ��ġ�� ��ȯ
	tPoint GetCamFocus()  {	return m_ptFocus;	} // ī�޶� ���� �ٶ󺸰� �ִ� ��ġ ��ȯ
	void SetCamFocus(tPoint _ptPos) { m_ptFocus = _ptPos; } // ī�޶� ��÷ ����
	POINT GetMousePos(); // ���콺 ��ġ�� ���� ī�޶� �������� ����

public:
	CCamera();
	~CCamera();
};

