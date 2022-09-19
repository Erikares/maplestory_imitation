#pragma once

class CKeyMgr_60
{
	DECLARE_SINGLETONE(CKeyMgr_60)
#define MAX_VIRTUAL_KEY	0xEF
private:
	bool	m_bKey[MAX_VIRTUAL_KEY];
public:
	void	Update(void);

	bool	GetKeyState(int iKey);
	bool	GetKeyDown(int iKey);
	bool	GetKeyUp(int iKey);

private:
	CKeyMgr_60(void);
public:
	~CKeyMgr_60(void);
};
