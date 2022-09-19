#include "StdAfx.h"
#include "Atk.h"

CAtk::CAtk(void)
{
}

CAtk::CAtk(float fX, float fY, int iKey, eArrow dir, int iAtk)
{
	m_eArrow	= dir;
	m_tInfo.fX	= fX;
	m_tInfo.fY	= fY;
	m_iOption	= iKey;
	m_iDmg		= iAtk;

	m_iHitCount	= 0;

	m_bHit		= false;
	m_bUse		= false;
	m_bPlayer	= false;
	m_bPress	= false;

	m_dwTime	= GetTickCount();
	m_dwFrameTime
				= GetTickCount();

}

CAtk::~CAtk(void)
{
}

void CAtk::Initialize()
{
	switch(m_iOption)
	{
	case Atk_SHOOT:
		m_fStartPOS		=	0;
		m_tInfo.fCX		=	30;
		m_tInfo.fCY		=	7;
		m_bPlayer		=	true;
		break;
	
	case Atk_RINGSHOOT:
		m_fStartPOS		=	0;
		m_tInfo.fCX		=	80;
		m_tInfo.fCY		=	7;
		m_bPlayer		=	true;
		break;
	
	case Atk_DRIVER:
		if(m_eArrow == DIR_RIGHT)
		{
			m_tInfo.fX += 100;
		}
		else
			m_tInfo.fX -= 50;

		m_tInfo.fCX		=	300;
		m_tInfo.fCY		=	100;
		m_bPlayer		=	true;

		m_tFrame = FRAME(0, 7, 0, 100); 
		break;

	case Atk_HIGH:
		m_tInfo.fY		-=	200;
		m_tInfo.fCX		=	300;
		m_tInfo.fCY		=	400;
		m_bPlayer		=	true;

		m_tFrame = FRAME(0, 13, 0, 40); 
		break;

	case Atk_ENREAL:
		if(m_eArrow == DIR_RIGHT)
		{
			m_tInfo.fX += 350;
			m_tInfo.fY -= 145;
		}
		else
		{
			m_tInfo.fX -= 350;
			m_tInfo.fY -= 145;
		}

		m_tInfo.fCX		=	700;
		m_tInfo.fCY		=	350;
		m_bPlayer		=	true;

		m_tFrame = FRAME(0, 12, 0, 60); 
		break;

	case Atk_RING:
		m_tInfo.fCX		=	0;
		m_tInfo.fCY		=	0;
		m_bPlayer		=	true;

		m_tFrame = FRAME(0, 4, 0, 100); 
		break;

	
	case Atk_SKILL:
		m_bPlayer		=	true;
		break;
	}
}

int CAtk::Update()
{
	switch(m_iOption)
	{
	//일반공격
	case Atk_SHOOT:
		if(m_fStartPOS > 400)
			return 1;

		if(m_bHit)
		{
			return 1;
		}

		switch(m_eArrow)
		{
		case DIR_RIGHT:
			m_fStartPOS += 10;
			m_tInfo.fX += 10;
			break;
		case DIR_LEFT:
			m_fStartPOS += 10;
			m_tInfo.fX -= 10;
			break;
		}

		break;

	case Atk_RINGSHOOT:
		if(m_fStartPOS > 500)
			return 1;

		if(m_bHit)
		{
			return 1;
		}

		switch(m_eArrow)
		{
		case DIR_RIGHT:
			m_fStartPOS += 10;
			m_tInfo.fX += 10;
			break;
		case DIR_LEFT:
			m_fStartPOS += 10;
			m_tInfo.fX -= 10;
			break;
		}

		break;

	case Atk_DRIVER:

		//한번 사용 한 스킬은 이펙트만 남기고 타격 없음.
		if(m_bUse)
		{
			m_tInfo.fCX = 0;
			m_tInfo.fCY = 0;
		}
		else
			m_bUse = true;
		
		
		//스킬 사용 후 0.5초뒤 소멸
		if(m_dwTime + 800 < GetTickCount())
		{
			return 1;
		}
		break;

	case Atk_HIGH:

		if(m_bUse)
		{
			m_tInfo.fCX	= 0;
			m_tInfo.fCY	= 0;

			if(m_dwTime + 60 < GetTickCount() && m_iHitCount < 6)
			{
				m_bUse = false;
			}
			else if(m_dwTime + 100 < GetTickCount())
			{
				return 1;	//히트카운트 6을 채우고 0.3초가 지나면 소멸
			}
		}
		else
		{
			m_dwTime = GetTickCount();
			m_tInfo.fCX = 300;
			m_tInfo.fCY = 400;
			m_bUse = true;
			++m_iHitCount;		//타격 카운트 체크
		}
		break;

	case Atk_ENREAL:

		if(m_bUse)
		{
			m_tInfo.fCX	= 0;
			m_tInfo.fCY	= 0;

			if(m_dwTime + 60 < GetTickCount() && m_iHitCount < 10)
			{
				m_bUse = false;
			}
			else if(m_dwTime + 100 < GetTickCount())
			{
				return 1;	//히트카운트 6을 채우고 0.3초가 지나면 소멸
			}
		}
		else
		{
			m_dwTime = GetTickCount();
			m_tInfo.fCX = 700;
			m_tInfo.fCY = 350;
			m_bUse = true;
			++m_iHitCount;		//타격 카운트 체크
		}
		break;

	case Atk_RING:
		m_tInfo.fX = CObjMgr::GetInstance()->GetList(OBJ_PLY)->front()->GetInfo()->fX;
		m_tInfo.fY = CObjMgr::GetInstance()->GetList(OBJ_PLY)->front()->GetInfo()->fY;
		if(GetAsyncKeyState('X') && !m_bPress)
		{
			if(m_dwTime + 500 < GetTickCount())
			{
				m_bPress = true;
				m_tFrame = FRAME(0, 7, 1, 100); 
			}
		}

		if(!GetAsyncKeyState('X') && m_bPress)
		{
			m_tFrame = FRAME(0, 5, 2, 100); 
			m_bPress = false;
		}

		if(GetAsyncKeyState('X') && m_bPress)
		{

			if(m_dwTime + 200 < GetTickCount())
			{
				int iPosition	= 0;

				if(m_bUse)
				{
					iPosition	= 10;
					m_bUse		= false;
				}
				else if(!m_bUse)
				{
					iPosition	= -10;
					m_bUse		= true;
				}

				m_dwTime = GetTickCount();

				if(GetAsyncKeyState(VK_RIGHT))
					m_eArrow = DIR_RIGHT;

				if(GetAsyncKeyState(VK_LEFT))
					m_eArrow = DIR_LEFT;

				//탄환 생성
				CObj*	pObj = new CAtk(m_tInfo.fX,m_tInfo.fY + iPosition, Atk_RINGSHOOT, m_eArrow, m_iDmg);
				pObj->Initialize();

				CSoundMgr::GetInstance()->PlaySound(L"ring_arrow.mp3");

				CObjMgr::GetInstance()->AddObj(pObj, OBJ_ATK);
			}

		}

		if(!GetAsyncKeyState('X') && !m_bPress)
		{
			if(m_dwTime + 580 < GetTickCount())
			{
				return 1;
			}
		}

	}
	CObj::Update();

	return 0;
}

void CAtk::HitCheck(bool bCheck)
{
	m_bHit = bCheck;
}

int CAtk::GetDmg(int iType)
{
	switch(iType)
	{
	case Atk_SHOOT:
		return static_cast<int>(m_iDmg + ((m_iDmg / 100) * (rand() % 10)));
		//데미지100% + 데미지1~10%

	case Atk_RINGSHOOT:
		return static_cast<int>(m_iDmg + ((m_iDmg / 100) * (rand() % 10)) * 2.2);
		//데미지100% + 데미지1~10%

	case Atk_DRIVER:
		return static_cast<int>((m_iDmg * 1.2) + ((rand() % (m_iDmg / 10))));
		//데미지120% + 데미지1~10% 랜덤

	case Atk_HIGH:
		return static_cast<int>((m_iDmg - (m_iDmg * 0.1)) + (rand() % (m_iDmg / 2)));
		//데미지90% + 데미지 50% 랜덤
	case Atk_ENREAL:
		return static_cast<int>((m_iDmg * 2) + (rand() % (m_iDmg / 10)));
		//데미지200% + 데미지1~10%
	}

	return 0;
}

void CAtk::Render()
{
		//Rectangle(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
		//m_Rect.left + m_ptScroll.x,
		//m_Rect.top + m_ptScroll.y,
		//m_Rect.right + m_ptScroll.x,
		//m_Rect.bottom + m_ptScroll.y);

	switch(m_iOption)
	{
	//일반공격
	case Atk_SHOOT:

		switch(m_eArrow)
		{
		case DIR_RIGHT:
			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
				static_cast<int>(m_tInfo.fX - (m_tInfo.fCX / 2) + m_ptScroll.x),
				static_cast<int>(m_tInfo.fY - (m_tInfo.fCY / 2) + m_ptScroll.y),
				30,
				7,
				CBitMgr::GetInstance()->GetImage(L"Arrow_Right"),
				0,
				0,
				30,
				7,
				RGB(140, 203, 157));
			break;

		case DIR_LEFT:
			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
				static_cast<int>(m_tInfo.fX - (m_tInfo.fCX / 2) + m_ptScroll.x),
				static_cast<int>(m_tInfo.fY - (m_tInfo.fCY / 2) + m_ptScroll.y),
				30,
				7,
				CBitMgr::GetInstance()->GetImage(L"Arrow_Left"),
				0,
				0,
				30,
				7,
				RGB(140, 203, 157));
			break;
		}
		break;

	case Atk_RINGSHOOT:

		switch(m_eArrow)
		{
		case DIR_RIGHT:
			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
				static_cast<int>(m_tInfo.fX - 40 + m_ptScroll.x),
				static_cast<int>(m_tInfo.fY - 4 + m_ptScroll.y),
				80,
				7,
				CBitMgr::GetInstance()->GetImage(L"Left_Ring_Arrow"),
				0,
				0,
				80,
				7,
				RGB(248, 255, 217));
			break;

		case DIR_LEFT:
			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
				static_cast<int>(m_tInfo.fX - 40 + m_ptScroll.x),
				static_cast<int>(m_tInfo.fY - 4 + m_ptScroll.y),
				80,
				7,
				CBitMgr::GetInstance()->GetImage(L"Left_Ring_Arrow"),
				0,
				0,
				80,
				7,
				RGB(248, 255, 217));
			break;
		}
		break;

	case Atk_DRIVER:

		TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
			static_cast<int>(m_tInfo.fX - 95 + m_ptScroll.x),
			static_cast<int>(m_tInfo.fY - 249 + m_ptScroll.y),
			190,
			368,
			CBitMgr::GetInstance()->GetImage(L"Charge_Drive"),
			0,
			368 * m_tFrame.iFrameStart,
			190,
			368,
			RGB(0, 114, 255));

		//프레임 값 증가

		if(m_dwFrameTime + m_tFrame.dwFrameTime < GetTickCount())
		{
			m_dwFrameTime = GetTickCount();

			++m_tFrame.iFrameStart;
			if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
				m_tFrame.iFrameStart = 0;
		}
		break;

	case Atk_HIGH:

		TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
			static_cast<int>(m_tInfo.fX - 277 + m_ptScroll.x),
			static_cast<int>(m_tInfo.fY - 192 + m_ptScroll.y),
			544,
			384,
			CBitMgr::GetInstance()->GetImage(L"High_Kick"),
			0,
			384 * m_tFrame.iFrameStart,
			544,
			384,
			RGB(0, 114, 255));

		//프레임 값 증가

		if(m_dwFrameTime + m_tFrame.dwFrameTime < GetTickCount())
		{
			m_dwFrameTime = GetTickCount();

			++m_tFrame.iFrameStart;
			if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
				m_tFrame.iFrameStart = 0;
		}
		break;

	case Atk_ENREAL:
		switch(m_eArrow)
		{
		case DIR_RIGHT:
			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
				static_cast<int>(m_tInfo.fX - 400 + m_ptScroll.x),
				static_cast<int>(m_tInfo.fY - 185 + m_ptScroll.y),
				757,
				367,
				CBitMgr::GetInstance()->GetImage(L"Right_Enreal"),
				0,
				367 * m_tFrame.iFrameStart,
				757,
				367,
				RGB(255, 101, 119));
			break;
		case DIR_LEFT:
			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
				static_cast<int>(m_tInfo.fX - 350 + m_ptScroll.x),
				static_cast<int>(m_tInfo.fY - 185 + m_ptScroll.y),
				757,
				367,
				CBitMgr::GetInstance()->GetImage(L"Left_Enreal"),
				0,
				367 * m_tFrame.iFrameStart,
				757,
				367,
				RGB(255, 101, 119));
			break;
		}
			//프레임 값 증가

			if(m_dwFrameTime + m_tFrame.dwFrameTime < GetTickCount())
			{
				m_dwFrameTime = GetTickCount();

				++m_tFrame.iFrameStart;
				if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
					m_tFrame.iFrameStart = 0;
			}
		
		break;

	case Atk_RING:

		switch(m_eArrow)
		{
		case DIR_RIGHT:
			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
				static_cast<int>(m_tInfo.fX - 170 + m_ptScroll.x),
				static_cast<int>(m_tInfo.fY - 215 + m_ptScroll.y),
				382,
				369,
				CBitMgr::GetInstance()->GetImage(L"Right_Ring"),
				382 * m_tFrame.iScene,
				369 * m_tFrame.iFrameStart,
				382,
				369,
				RGB(248, 255, 217));
			break;

		case DIR_LEFT:
			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
				static_cast<int>(m_tInfo.fX - 200 + m_ptScroll.x),
				static_cast<int>(m_tInfo.fY - 215 + m_ptScroll.y),
				382,
				369,
				CBitMgr::GetInstance()->GetImage(L"Left_Ring"),
				382 * m_tFrame.iScene,
				369 * m_tFrame.iFrameStart,
				382,
				369,
				RGB(248, 255, 217));
			break;
		}

			cout << "Frameeeeee : " << m_tFrame.iFrameStart << endl;
			//프레임 값 증가
			if(m_dwFrameTime + m_tFrame.dwFrameTime < GetTickCount())
			{
				m_dwFrameTime = GetTickCount();

				++m_tFrame.iFrameStart;
				if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
					m_tFrame.iFrameStart = 0;
			}
		break;

	case Atk_SKILL:
		break;
	}



}

void CAtk::Release()
{
}