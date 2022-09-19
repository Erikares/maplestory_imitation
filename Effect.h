#pragma once
#include "obj.h"
#include "BitMgr.h"

class CEffect :	public CObj
{

private:
	int			iDmgNum;
	eAtkType	eType;	//��ų Ÿ��
	bool		Player;	//����Ʈ �������� �÷��̾����� ����

	int			iWidth;		//���ҽ� ���� ������
	int			iHeight;	//���ҽ� ���� ������

	int			iFrameCount;

	DWORD		m_dwTime;

	//������ ����Ʈ ����
	bool		b100000;
	bool		b10000;
	bool		b1000;
	bool		b100;
	bool		b10;
	bool		b1;

public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CEffect(void);
	CEffect(float, float, int, eAtkType, bool);
	virtual ~CEffect(void);
};
