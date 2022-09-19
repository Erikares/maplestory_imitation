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
	bool		m_bIsAtk;			//공격중 유무
	bool		m_bIsJump;			//점프 유무
	bool		m_bIsKnockBack;		//넉백 유무
	bool		m_bIsFall;			//추락 유무

	float		m_fJumpAcc;			//점프 가속도
	float		m_fKnockBack;		//넉백 수치

	int			m_iAction;
	DWORD		m_dwActiveTime;		//활동 시간
	DWORD		m_dwActive;
	DWORD		m_dwDeadTime;		//죽은뒤 사라지는 시간
	DWORD		m_dwFrameTime;

	DWORD		m_dwState;			//몬스터 상태
	DWORD		m_dwPrevState;
	FRAME		m_tFrame;			//몬스터 프레임

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
