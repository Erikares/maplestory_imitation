#pragma once
#include "obj.h"
#include "Effect.h"

#include "ObjMgr.h"
#include "BitMgr.h"

class CMonster : public CObj
{
protected:
	int			m_iMonType;
	PINFO		m_tMonster;

	float		m_fSpeed;

	eArrow		m_eArrow;
	bool		m_bIsAtk;			//������ ����
	bool		m_bIsJump;			//���� ����
	bool		m_bIsKnockBack;		//�˹� ����
	bool		m_bIsFall;			//�߶� ����

	float		m_fJumpAcc;			//���� ���ӵ�
	float		m_fKnockBack;		//�˹� ��ġ

	int			m_iAction;
	DWORD		m_dwActiveTime;		//Ȱ�� �ð�
	DWORD		m_dwActive;
	DWORD		m_dwDeadTime;		//������ ������� �ð�
	DWORD		m_dwFrameTime;

	DWORD		m_dwState;			//���� ����
	DWORD		m_dwPrevState;
	FRAME		m_tFrame;			//���� ������

	int			m_iBlend;

public:
	bool		m_bIsGhost;

public:
	void		TileCrush(TILE* _Tile);
	int			MoveCheck(void);
	int			GetDmg(void);
	void		FrameMove(void);

public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

	void	HpMgr(int _iDmg, int iAtkType, eArrow e_Arrow);

public:
	CMonster(void);
	CMonster(float _fX, float _fY, int iType);
	virtual ~CMonster(void);
};
