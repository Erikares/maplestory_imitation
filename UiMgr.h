#pragma once
#include "Scene.h"
#include "Start.h"
#include "Stage1.h"
#include "UI.h"

class CUiMgr
{
	DECLARE_SINGLETONE(CUiMgr)
private:
	vector<CUI*>	m_vecUiList;
	CUI*			m_tempUi;

public:
	void AddUi(CUI* pUi, TCHAR* pUiName)
	{
		pUi->m_pName = pUiName;
		m_vecUiList.push_back(pUi);
	}

	void Update(void);
	void Render(void);
	void Release(void);

	void RankSort(void);	//â�� �������� �� �� ���� â�� ���� �ǰ�,

private:
	CUiMgr(void);
public:
	virtual ~CUiMgr(void);
};
