#pragma once
#include "monster.h"
#include "obj.h"
#include "BitMgr.h"

class CSnowMan : public CMonster
{
public:
	void		TileCrush(TILE* _Tile);
	void		MoveCheck(void);
	void		FrameMove(void);

public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

	void	HpMgr(int _iDmg, int iAtkType, eArrow e_Arrow);

public:
	CSnowMan(void);
	virtual ~CSnowMan(void);
};
