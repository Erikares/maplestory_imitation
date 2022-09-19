#pragma once
#include "scene.h"
#include "BitMgr.h"
#include "ObjMgr.h"

#include "Player.h"
#include "Monster.h"

class CStage2 : public CScene
{
private:
	int				TILECOUNTX;
	int				TILECOUNTY;
	vector<TILE*>	m_vecTile;
	list<CObj*>*	m_pListMon;

	DWORD			m_dwTime;

	bool			m_ViewTile;
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

	void	TileCrush(void);

	void	SetMonList(list<CObj*>* pListMon)
	{
		m_pListMon = pListMon;
	}

public:
	CStage2(void);
	virtual ~CStage2(void);
};
