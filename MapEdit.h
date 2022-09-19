#pragma once
#include "scene.h"

class CMapEdit :
	public CScene
{
private:
	int					TILECOUNTX;
	int					TILECOUNTY;

	vector<TILE*>		m_vecTile;
	float				m_fScrollX;
	float				m_fScrollY;
public:
	void	SaveData(void);
	void	LoadData(void);
	void	Picking(void);
	void	KeyCheck(void);
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CMapEdit(void);
	virtual ~CMapEdit(void);
};
