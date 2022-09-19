#include "StdAfx.h"
#include "Effect.h"

CEffect::CEffect(void)
{
}

CEffect::CEffect(float _fX, float _fY, int _iDmgNum, eAtkType e_Type, bool _Player)
{
	m_tInfo.fX	= _fX;
	m_tInfo.fY	= _fY - 100;
	iDmgNum		= _iDmgNum;
	eType		= e_Type;		//이펙트의 종류(플레이어 스킬의 종류)
	Player		= _Player;	

	m_dwTime	= GetTickCount();

	iFrameCount	= 0;


	b100000		= false;
	b10000		= false;
	b1000		= false;
	b100		= false;
	b10			= false;
	b1			= false;


}

CEffect::~CEffect(void)
{
	Release();
}

void CEffect::Initialize(void)
{
	//데미지 자릿수 확인
	if(eType == Atk_DMG)
	{
		if(iDmgNum >= 100000)
			b100000 = true;
		if(iDmgNum >= 10000)
			b10000	= true;
		if(iDmgNum >= 1000)
			b1000	= true;
		if(iDmgNum >= 100)
			b100	= true;
		if(iDmgNum >= 10)
			b10		= true;
		if(iDmgNum >= 1)
			b1		= true;
	}

	if(!Player)	//몬스터로 인한 이펙트일 경우
	{
		switch(eType)
		{
		case Atk_DMG:	//데미지 수치
			m_tInfo.fCX		=	150;
			m_tInfo.fCY		=	70;
			m_pName			=	L"DamageEffect";
			break;
		}
	}
	else if(Player)	//플레이어에 의한 이펙트일 경우
	{
		switch(eType)
		{
		case Atk_DMG:	//데미지 수치
			m_tInfo.fCX		=	150;
			m_tInfo.fCY		=	70;
			m_pName			=	L"HitEffect";
			break;
		case OBJ_PORTAL:
			m_tInfo.fCX	=	89;
			m_tInfo.fCY	=	257;
			m_pName			=	L"Portal";
			break;
		}
	}
}

int CEffect::Update(void)
{
	switch(eType)
	{
	case Atk_DMG:	//데미지 수치\

		m_tInfo.fY -= 0.3f;

		if(m_dwTime + 1200 < GetTickCount())
			return 1;

		break;
	}
	CObj::Update();
	return 0;
}

void CEffect::Render(void)
{
	switch(eType)
	{
	case Atk_DMG:	//데미지 수치
		if(b100000)
		{
			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
				,static_cast<int>(m_tInfo.fX - m_tInfo.fCX / 2 - 75) + m_ptScroll.x
				,static_cast<int>(m_tInfo.fY - m_tInfo.fCY / 2) + m_ptScroll.y
				,150
				,70
				,CBitMgr::GetInstance()->GetImage(m_pName)
				, (iDmgNum / 100000) * 150
				, 0
				, 150
				, 70
				, RGB(66, 66, 66));
		}

		if(b10000)
		{
			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
				,static_cast<int>(m_tInfo.fX - m_tInfo.fCX / 2 - 50) + m_ptScroll.x
				,static_cast<int>(m_tInfo.fY - m_tInfo.fCY / 2) + m_ptScroll.y
				,150
				,70
				,CBitMgr::GetInstance()->GetImage(m_pName)
				, ((iDmgNum % 100000) / 10000) * 150
				, 0
				, 150
				, 70
				, RGB(66, 66, 66));
		}

		if(b1000)
		{
			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
				,static_cast<int>(m_tInfo.fX - m_tInfo.fCX / 2 - 25) + m_ptScroll.x
				,static_cast<int>(m_tInfo.fY - m_tInfo.fCY / 2) + m_ptScroll.y
				,150
				,70
				,CBitMgr::GetInstance()->GetImage(m_pName)
				, (((iDmgNum % 100000) % 10000) / 1000) * 150
				, 0
				, 150
				, 70
				, RGB(66, 66, 66));
		}

		if(b100)
		{
			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
				,static_cast<int>(m_tInfo.fX - m_tInfo.fCX / 2) + m_ptScroll.x
				,static_cast<int>(m_tInfo.fY - m_tInfo.fCY / 2) + m_ptScroll.y
				,150
				,70
				,CBitMgr::GetInstance()->GetImage(m_pName)
				, ((((iDmgNum % 100000) % 10000) % 1000) / 100) * 150
				, 0
				, 150
				, 70
				, RGB(66, 66, 66));
		}

		if(b10)
		{
			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
				,static_cast<int>(m_tInfo.fX - m_tInfo.fCX / 2 + 25) + m_ptScroll.x
				,static_cast<int>(m_tInfo.fY - m_tInfo.fCY / 2) + m_ptScroll.y
				,150
				,70
				,CBitMgr::GetInstance()->GetImage(m_pName)
				, (((((iDmgNum % 100000) % 10000) % 1000) % 100) / 10) * 150
				, 0
				, 150
				, 70
				, RGB(66, 66, 66));
		}

		if(b1)
		{
			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
				,static_cast<int>(m_tInfo.fX - m_tInfo.fCX / 2 + 50) + m_ptScroll.x
				,static_cast<int>(m_tInfo.fY - m_tInfo.fCY / 2) + m_ptScroll.y
				,150
				,70
				,CBitMgr::GetInstance()->GetImage(m_pName)
				, ((((((iDmgNum % 100000) % 10000) % 1000) % 100) % 10) / 1) * 150
				, 0
				, 150
				, 70
				, RGB(66, 66, 66));
		}
		break;

	case OBJ_PORTAL:
		TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
			,static_cast<int>(m_tInfo.fX - 45) + m_ptScroll.x
			,static_cast<int>(m_tInfo.fY - 128) + m_ptScroll.y
			,89
			,257
			,CBitMgr::GetInstance()->GetImage(m_pName)
			, 89 * iFrameCount
			, 0
			, 89
			, 257
			, RGB(255, 255, 255));

		if(m_dwTime + 100 < GetTickCount())
		{
			m_dwTime = GetTickCount();
			++iFrameCount;
		}

		if(iFrameCount > 7)
			iFrameCount = 0;


		break;
	}

}

void CEffect::Release(void)
{
}