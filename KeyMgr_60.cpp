#include "StdAfx.h"
#include "KeyMgr_60.h"

IMPLEMENT_SINGLETONE(CKeyMgr_60)

CKeyMgr_60::CKeyMgr_60(void)
{
	memset(m_bKey, 0, sizeof(m_bKey));
}

CKeyMgr_60::~CKeyMgr_60(void)
{
}

void CKeyMgr_60::Update(void)
{
	for(int i = 0; i < MAX_VIRTUAL_KEY; ++i)
	{
		if(!m_bKey[i] && GetAsyncKeyState(i))
			m_bKey[i] = !m_bKey[i];
		else if(m_bKey[i] && !GetAsyncKeyState(i))
			m_bKey[i] = !m_bKey[i];
	}
}

bool CKeyMgr_60::GetKeyState(int iKey)
{
	if(GetAsyncKeyState(iKey) & 0x8001)
		return true;

	return false;
}

bool CKeyMgr_60::GetKeyDown(int iKey)
{
	if(!m_bKey[iKey] && GetAsyncKeyState(iKey))
	{
		m_bKey[iKey] = !m_bKey[iKey];
		return true;
	}
	return false;
}

bool CKeyMgr_60::GetKeyUp(int iKey)
{
	if(m_bKey[iKey] && !GetAsyncKeyState(iKey))
	{
		m_bKey[iKey] = !m_bKey[iKey];
		return true;
	}
	return false;
}


