#pragma once
#include "obj.h"

class CMouse :
	public CObj
{
public:
	static POINT	GetPos(void);
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CMouse(void);
	virtual ~CMouse(void);
};
