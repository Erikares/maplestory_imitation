#include "StdAfx.h"
#include "UiMgr.h"
IMPLEMENT_SINGLETONE(CUiMgr)
CUiMgr::CUiMgr(void)
:m_tempUi(NULL)
{
}

CUiMgr::~CUiMgr(void)
{
	Release();
}


void CUiMgr::Update(void)
{
	vector<CUI*>::iterator iter		=	m_vecUiList.begin();
	vector<CUI*>::iterator iter_end	=	m_vecUiList.end();

	//if(CKeyMgr_60::GetInstance()->GetKeyDown('I'))
	
	//�κ�â ��� �� �ֻ�����
	if(GetAsyncKeyState('I') & 1)
	{
		for(iter; iter != iter_end; ++iter)
		{
			if(!lstrcmp((*iter)->m_pName, L"InvenUI"))
			{
				if((*iter)->m_Act == true)
				{
					(*iter)->m_Act = false;
					break;
				}
				else if((*iter)->m_Act == false)
				{
					(*iter)->m_Act = true;
					CUI* pTempUi = (*iter);
					iter = m_vecUiList.erase(iter);
					m_vecUiList.push_back(pTempUi);
					break;
				}
			}
		}
	}

	iter = m_vecUiList.begin();
	iter_end = m_vecUiList.end();
	//���â ��� �� �ֻ�����
	if(GetAsyncKeyState('E') & 1)
	{
		for(iter; iter != iter_end; ++iter)
		{
			if(!lstrcmp((*iter)->m_pName, L"EquipUI"))
			{
				if((*iter)->m_Act == true)
				{
					(*iter)->m_Act = false;
					break;
				}
				else if((*iter)->m_Act == false)
				{
					(*iter)->m_Act = true;
					CUI* pTempUi = (*iter);
					iter = m_vecUiList.erase(iter);
					m_vecUiList.push_back(pTempUi);
					break;
				}
			}
		}
	}

	iter = m_vecUiList.begin();
	iter_end = m_vecUiList.end();
	//��ųâ ��� �� �ֻ�����
	if(GetAsyncKeyState('K') & 1)
	{
		for(iter; iter != iter_end; ++iter)
		{
			if(!lstrcmp((*iter)->m_pName, L"SkillUI"))
			{
				if((*iter)->m_Act == true)
				{
					(*iter)->m_Act = false;
					break;
				}
				else if((*iter)->m_Act == false)
				{
					(*iter)->m_Act = true;
					CUI* pTempUi = (*iter);
					iter = m_vecUiList.erase(iter);
					m_vecUiList.push_back(pTempUi);
					break;
				}
			}
		}
	}

	iter = m_vecUiList.begin();
	iter_end = m_vecUiList.end();
	//����â ��� �� �ֻ�����
	if(GetAsyncKeyState('S') & 1)
	{
		for(iter; iter != iter_end; ++iter)
		{
			if(!lstrcmp((*iter)->m_pName, L"StateUI"))
			{
				if((*iter)->m_Act == true)
				{
					(*iter)->m_Act = false;
					break;
				}
				else if((*iter)->m_Act == false)
				{
					(*iter)->m_Act = true;
					CUI* pTempUi = (*iter);
					iter = m_vecUiList.erase(iter);
					m_vecUiList.push_back(pTempUi);
					break;
				}
			}
		}
	}

	iter = m_vecUiList.begin();
	iter_end = m_vecUiList.end();
	

	for(iter ; iter != iter_end; ++iter)
	{
		(*iter)->Update();
	}

	RankSort();
}

void CUiMgr::Render(void)
{
	vector<CUI*>::iterator iter		=	m_vecUiList.begin();
	vector<CUI*>::iterator iter_end	=	m_vecUiList.end();

	for(iter ; iter != iter_end; ++iter)
	{
		(*iter)->Render();
	}
}

void CUiMgr::Release(void)
{
	vector<CUI*>::iterator iter = m_vecUiList.begin();
	vector<CUI*>::iterator iter_end = m_vecUiList.end();

	for(iter; iter != iter_end; ++iter)
	{
		delete (*iter);
	}
	m_vecUiList.clear();
}

//â�� Ŭ������ ��, Ŭ���� ��Ʈ�� �ֻ����� ����
void CUiMgr::RankSort(void)
{
	vector<CUI*>::iterator iter		=	m_vecUiList.begin();
	vector<CUI*>::iterator iter_end	=	m_vecUiList.end();

	for(iter; iter != iter_end; ++iter)
	{
		(*iter)->m_DragAct = false;

		if(true == (*iter)->HighRect())
		{
			m_tempUi = (*iter);
		}
	}

	iter = m_vecUiList.begin();
	iter_end = m_vecUiList.end();

	if(m_tempUi != NULL)
	{
		for(iter; iter != iter_end; ++iter)
		{
			if(!lstrcmp((*iter)->m_pName, m_tempUi->m_pName))
			{
				(*iter)->m_DragAct = true;

				m_vecUiList.erase(iter);
				m_vecUiList.push_back(m_tempUi);
				m_tempUi = NULL;
				break;
			}
		}
	}

}