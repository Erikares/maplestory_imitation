#pragma once
#include "obj.h"

class CBackGround :	public CObj
{
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CBackGround(void);
	virtual ~CBackGround(void);
};