#pragma once

class CObj
{
protected:
	//½ºÅ©·Ñ 
	TCHAR*			m_pName;
	RECT			m_Rect;
	INFO			m_tInfo;


public:
	virtual void Initialize(void) PURE;
	virtual int Update(void);
	virtual void Render(void) PURE;
	virtual void Release(void) PURE;

	INFO*	GetInfo(void)
	{
		return &m_tInfo;
	}

	RECT*	GetRect(void)
	{
		return &m_Rect;
	}

public:
	CObj(void);
	virtual ~CObj(void);
};
