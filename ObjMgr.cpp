#include "StdAfx.h"
#include "ObjMgr.h"

IMPLEMENT_SINGLETONE(CObjMgr)
CObjMgr::CObjMgr(void)
{
}

CObjMgr::~CObjMgr(void)
{
	Release();
}

void CObjMgr::Update()
{
	HitRect();

	for(int i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator iter		=	m_ObjList[i].begin();
		list<CObj*>::iterator iter_end	=	m_ObjList[i].end();

		for(; iter != iter_end; )
		{
			if(1 == (*iter)->Update())
			{
				delete (*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;

			//ATK �����������̸���

		}
	}
}

void CObjMgr::Render()
{
	for(int i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator iter		=	m_ObjList[i].begin();
		list<CObj*>::iterator iter_end	=	m_ObjList[i].end();

		for(; iter != iter_end; ++iter)
		{
			(*iter)->Render();
		}
	}
}

void CObjMgr::Release()
{
	for(int i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator iter		=	m_ObjList[i].begin();
		list<CObj*>::iterator iter_end	=	m_ObjList[i].end();

		for(; iter != iter_end; ++iter)
		{
			delete (*iter);
		}
		m_ObjList[i].clear();
	}
}

void	CObjMgr::HitRect(void)
{
	RECT rc;

	list<CObj*>::iterator iter = m_ObjList[OBJ_MON].begin();
	list<CObj*>::iterator iter_end = m_ObjList[OBJ_MON].end();

	for(iter; iter != iter_end; ++iter)
	{
		//�÷��̾� ����
		CObj* pPlayer = m_ObjList[OBJ_PLY].front();

		if(TRUE == IntersectRect(&rc, (*iter)->GetRect(), pPlayer->GetRect()))
		{
			//cout << "���� ����!" << endl;

			eArrow e_Arrow;

			if((*iter)->GetInfo()->fX > pPlayer->GetInfo()->fX)
			{
				e_Arrow = DIR_RIGHT;	//������ ���Ϳ��� �ǰ�
			}
			else
			{
				e_Arrow = DIR_LEFT;		//���� ���Ϳ��� �ǰ�
			}
			if(!static_cast<CPlayer*>(pPlayer)->m_bIsSuper)
			{
				static_cast<CPlayer*>(pPlayer)->HpMgr(static_cast<CMonster*>(*iter)->GetDmg(), 0, e_Arrow);
			}
			else
				cout << "�����ε�" << endl;

		}



		list<CObj*>::iterator AtkIter = m_ObjList[OBJ_ATK].begin();
		list<CObj*>::iterator AtkIter_end = m_ObjList[OBJ_ATK].end();

		for(AtkIter; AtkIter != AtkIter_end; ++AtkIter)
		{
			if(TRUE == IntersectRect(&rc, (*iter)->GetRect(), (*AtkIter)->GetRect()))
			{
				//������ �÷��̾�κ��� ���°�����
				if(static_cast<CAtk*>(*AtkIter)->m_bPlayer)
				{
					eArrow e_Arrow;		//���� ��

					//���Ͱ� �ǰݹ��� ��ġ ��
					if((*iter)->GetInfo()->fX > (*AtkIter)->GetInfo()->fX)
					{
						e_Arrow = DIR_RIGHT; //�����ʿ��� ���ƿ� ����
					}
					else
					{
						e_Arrow = DIR_LEFT;	 //���ʿ��� ���ƿ� ����
					}
					
					int	iOption = static_cast<CAtk*>(*AtkIter)->m_iOption;
					static_cast<CMonster*>(*iter)->HpMgr(static_cast<CAtk*>(*AtkIter)->GetDmg(iOption), iOption, e_Arrow);

					//��Ʈ ���� ����
					static_cast<CAtk*>(*AtkIter)->HitCheck(true);
				}
			}
		}
	}

}