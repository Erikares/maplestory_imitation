#pragma once
#include "obj.h"

class CTile : public CObj
{

public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CTile(void);
	virtual ~CTile(void);
};
