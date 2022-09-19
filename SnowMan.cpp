#include "StdAfx.h"
#include "SnowMan.h"

CSnowMan::CSnowMan(void)
{
}

CSnowMan::CSnowMan(float _fX, float _fY, int iType)
{
	m_tInfo.fX 		= 	_fX;
	m_tInfo.fY 		= 	_fY;

	m_eArrow		=	DIR_RIGHT;
	m_bIsAtk		=	false;
	m_bIsJump		=	false;
	m_bIsFall		=	false;

	m_fJumpAcc		=	0.f;
	m_fKnockBack	=	0.f;

	switch(iType)
	{
	case MON1:

		break;

	case MON2:
		
		break;

	case MON3:
		
		break;
	}

}

CSnowMan::~CSnowMan(void)
{
}
