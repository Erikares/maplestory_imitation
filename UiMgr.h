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

	void RankSort(void);	//창이 겹쳐있을 때 최 상위 창만 선택 되게,

private:
	CUiMgr(void);
public:
	virtual ~CUiMgr(void);
};
