#pragma once
#include "Player.h"
#include "Scene.h"
#include "BitMgr.h"
#include "ObjMgr.h"
#include "Mouse.h"

class CSceneMgr;
class CStart : public CScene
{
private:
	vector<TILE*>	m_vecTile;
	int				m_ButtonState;

	RECT			m_rcStart;
	POINT			ptPoint;


public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CStart(void);
	virtual ~CStart(void);
};
