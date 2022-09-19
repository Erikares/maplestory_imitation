#pragma once
#include "obj.h"

#include "ObjMgr.h"
#include "Player.h"
#include "BitMgr.h"

class CAtk : public CObj
{
private:
	eArrow	m_eArrow;
	float	m_fStartPOS;
	int		m_iDmg;
	int		m_iHitCount;//Ÿ�� Ƚ�� üũ

	bool	m_bHit;		//Ÿ�� ����
	bool	m_bUse;		//1ȸ�� ��ų ��� ����
	bool	m_bPress;	//������ ��ų �Է� ����

	DWORD	m_dwTime;	//���� Ÿ�� üũ
	DWORD	m_dwFrameTime;	//������ ��ȯ �ð�
	FRAME	m_tFrame;	//��ų ������ ��ǥ ����


public:
	int		m_iOption;	//��ų�� ����
	bool	m_bPlayer;	//������ �÷��̾� ����

public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

	void	HitCheck(bool bCheck);
	int		GetDmg(int iType);

public:
	CAtk(void);
	CAtk(float, float, int, eArrow, int);
	virtual ~CAtk(void);
};
