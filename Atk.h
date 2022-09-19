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
	int		m_iHitCount;//타격 횟수 체크

	bool	m_bHit;		//타격 유무
	bool	m_bUse;		//1회성 스킬 사용 여부
	bool	m_bPress;	//반응형 스킬 입력 여부

	DWORD	m_dwTime;	//공격 타임 체크
	DWORD	m_dwFrameTime;	//프레임 변환 시간
	FRAME	m_tFrame;	//스킬 프레임 좌표 설정


public:
	int		m_iOption;	//스킬의 종류
	bool	m_bPlayer;	//발현지 플레이어 유무

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
