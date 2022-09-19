#pragma once
#include "scene.h"
#include "BitMgr.h"
#include "ObjMgr.h"

#include "Player.h"
#include "Monster.h"

class CStage1 : public CScene
{
private:
	int				TILECOUNTX;
	int				TILECOUNTY;
	vector<TILE*>	m_vecTile;
	list<CObj*>*	m_pListMon;

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
	CStage1(void);
	virtual ~CStage1(void);
};
