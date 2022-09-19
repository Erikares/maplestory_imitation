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

			//ATK 오브제업데이를ㄹ

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
		//플레이어 대입
		CObj* pPlayer = m_ObjList[OBJ_PLY].front();

		if(TRUE == IntersectRect(&rc, (*iter)->GetRect(), pPlayer->GetRect()))
		{
			//cout << "공격 받음!" << endl;

			eArrow e_Arrow;

			if((*iter)->GetInfo()->fX > pPlayer->GetInfo()->fX)
			{
				e_Arrow = DIR_RIGHT;	//오른쪽 몬스터에게 피격
			}
			else
			{
				e_Arrow = DIR_LEFT;		//왼쪽 몬스터에게 피격
			}
			if(!static_cast<CPlayer*>(pPlayer)->m_bIsSuper)
			{
				static_cast<CPlayer*>(pPlayer)->HpMgr(static_cast<CMonster*>(*iter)->GetDmg(), 0, e_Arrow);
			}
			else
				cout << "무적인뎅" << endl;

		}



		list<CObj*>::iterator AtkIter = m_ObjList[OBJ_ATK].begin();
		list<CObj*>::iterator AtkIter_end = m_ObjList[OBJ_ATK].end();

		for(AtkIter; AtkIter != AtkIter_end; ++AtkIter)
		{
			if(TRUE == IntersectRect(&rc, (*iter)->GetRect(), (*AtkIter)->GetRect()))
			{
				//공격이 플레이어로부터 나온것인지
				if(static_cast<CAtk*>(*AtkIter)->m_bPlayer)
				{
					eArrow e_Arrow;		//방향 값

					//몬스터가 피격받은 위치 값
					if((*iter)->GetInfo()->fX > (*AtkIter)->GetInfo()->fX)
					{
						e_Arrow = DIR_RIGHT; //오른쪽에서 날아온 공격
					}
					else
					{
						e_Arrow = DIR_LEFT;	 //왼쪽에서 날아온 공격
					}
					
					int	iOption = static_cast<CAtk*>(*AtkIter)->m_iOption;
					static_cast<CMonster*>(*iter)->HpMgr(static_cast<CAtk*>(*AtkIter)->GetDmg(iOption), iOption, e_Arrow);

					//히트 여부 리턴
					static_cast<CAtk*>(*AtkIter)->HitCheck(true);
				}
			}
		}
	}

}