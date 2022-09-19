#ifndef Struc_
#define Struc_

typedef struct tagInfo
{
	float fX;
	float fY;
	float fCX;
	float fCY;

	tagInfo(void) {}
	tagInfo(float _fX, float _fY, float _fCX, float _fCY)
		:fX(_fX), fY(_fY), fCX(_fCX), fCY(_fCY) {}
}INFO;

typedef struct tagPlayerInfo
{
	int		iHp;
	int		iMaxHp;
	int		iMp;
	int		iMaxMp;
	int		iGold;
	int		iAtk;
	int		iDef;
}PINFO;

class CItem;
typedef struct tEquipInfo
{
	CItem*	tHead;
	CItem*	tWeapon;
	CItem*	tArmor;
	CItem*	tGloves;
	CItem*	tBoots;

	tEquipInfo(int, int, int, int, int)
		:tHead(NULL), tWeapon(NULL), tArmor(NULL), tGloves(NULL), tBoots(NULL) {}
}EINFO;

typedef struct tagItemInfo
{
	int		eType;
	TCHAR*	pName;
	int 	iCode;
	int		iAtk;
	int		iDef;
	int		iAp;
	int 	iPrice;
}TINFO;

typedef struct tagQuick
{
	CItem*	pQuick1;
	CItem*	pQuick2;
	CItem*	pQuick3;
	CItem*	pQuick4;
	CItem*	pQuick5;
	CItem*	pQuick6;
	CItem*	pQuick7;
	CItem*	pQuick8;
}QSLOT;

typedef struct tagFrame
{
	int		iFrameStart;
	int		iFrameEnd;
	int		iScene;
	DWORD	dwFrameTime;

	tagFrame(void) {}
	tagFrame(int _iFrameStart, int _iFrameEnd, int _iScene, DWORD _dwFrameTime)
		:iFrameStart(_iFrameStart), iFrameEnd(_iFrameEnd), iScene(_iScene), dwFrameTime(_dwFrameTime){}
}FRAME;

typedef struct tagTile
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;
	int		iOption;
	int		iDrawID;
	tagTile(void){;}
	tagTile(float fX, float fY)
		:fX(fX), fY(fY)
	{
		this->fCX = TILESIZEX;
		this->fCY = TILESIZEY;
		this->iOption = 0;
		this->iDrawID = 0;
	}
}TILE;

//typedef struct tagAtk
//{
//	float	fX;
//	float	fY;
//	float	fCX;
//	float	fCY;
//	int		iOption;
//
//	tagAtk(void) {}
//	tagAtk(float fX, float fY, int iKey)
//		:fX(fX), fY(fY), iOption(iKey)
//	{}
//}ATK;
#endif