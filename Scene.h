#pragma once
#include "Obj.h"
#include "SoundMgr.h"


class CScene
{
protected:
	CObj*		m_pPlayer;

public:
	void	SetPlayer(CObj* pPlayer)
	{
		m_pPlayer = pPlayer;
	}

public:
	virtual void	Initialize(void)PURE;
	virtual int		Update(void)PURE;
	virtual void	Render(void)PURE;
	virtual void	Release(void)PURE;
public:
	CScene(void);
	virtual ~CScene(void);
};
