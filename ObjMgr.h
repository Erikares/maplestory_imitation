#pragma once
#include "Obj.h"
#include "Atk.h"

#include "Monster.h"
#include "Player.h"

class CObjMgr
{
	DECLARE_SINGLETONE(CObjMgr)
private:
	list<CObj*>			m_ObjList[OBJ_END];

public:

	void	AddObj(CObj* pObj, eObjList eType)
	{
		m_ObjList[eType].push_back(pObj);
	}

	list<CObj*>*	GetList(int ListNum)
	{
		return &m_ObjList[ListNum];
	}

	void	Update(void);
	void	Render(void);
	void	Release(void);
	void	HitRect(void);

private:
	CObjMgr(void);
public:
	virtual ~CObjMgr(void);
};
