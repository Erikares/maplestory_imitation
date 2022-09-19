#pragma once
#include "obj.h"
#include "Item.h"
#include "KeyMgr_60.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "Mouse.h"
#include "Atk.h"
//#include "MainUI.h"

class CItem;
//typedef struct tEquipInfo
//{
//	CItem*	tHead;
//	CItem*	tWeapon;
//	CItem*	tArmor;
//	CItem*	tGloves;
//	CItem*	tBoots;
//
//	tEquipInfo(int, int, int, int, int)
//		:tHead(NULL), tWeapon(NULL), tArmor(NULL), tGloves(NULL), tBoots(NULL) {}
//}EINFO;

class CPlayer : public CObj
{
private:
	PINFO			m_tPlayer;
	EINFO			m_tEquip;
	
	float			m_fSpeed;
	int				iItemNum;			//인벤 내의 아이템 순서를 체크
	POINT			pt;
	POINT			m_ptOffset;

private:	//행동 관련
	eArrow			m_eArrow;
	bool			m_bIsAtk;			//공격 중
	bool			m_bIsJump;			//점프 중
	bool			m_bIsFall;			//추락 중
	bool			m_bIsHit;			//맞는 중
	
	//스킬 관련
	bool			m_bIsSkilling;		//스킬 쓰는 중
	bool			m_bIsDrive;			//차지 드라이브 시전 중
	bool			m_bIsHigh;			//하이킥 데몰리션 시전 중
	bool			m_bIsRing;			//이슈타르 링 시전 중


	bool			m_bIsClimb;			//등반 가능
	bool			m_bIsGhost;			//타일 통과 가능
	bool			m_bIsHill;			//하향 점프 가능
	bool			m_bIsKnockBack;		//넉백 유무


	float			m_fJumpAcc;			//점프 가속도
	float			m_fKnockBack;		//넉백 수치

	float			m_fTime;

	bool			m_Drag;
	DWORD			m_dwActiveTime;		//피격 활성화 시간
	DWORD			m_dwItemTime;		//아이템 놓을때 일정 시간마다 적용되게 하기

	DWORD			m_dwState;			//플레이어의 현재상태
	DWORD			m_dwPrevState;		//플레이어의 이전상태
	
	FRAME			m_tFrame;			//캐릭터 프레임 좌표 설정

	DWORD			m_dwFrameTime;		

private:
	void			ItemSwap(void);
	void			ItemCrush(void);
	void			FrameMove(void);
	void			KeyCheck(void);
	void			Scroll(void);
	void			UseItem(CItem &pItem);
	
	vector<CItem*>	m_vecInven;
	vector<TILE*>*	m_pvecTile;
	list<CObj*>*	m_plistAtk;

public:
	void			TileCrush(TILE*	_Tile);

public:	//퀵슬롯
	QSLOT	m_Quick;

	int				m_iPrevMap;
	bool			m_bIsSuper;			//충돌무시
	
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

	void	HpMgr(int _iDmg, int iAtkType, eArrow e_Arrow);

	void	SetTile(vector<TILE*>* pTileVector)
	{
		m_pvecTile = pTileVector;
	}

	void	SetAtk(list<CObj*>* pAtkList)
	{
		m_plistAtk = pAtkList;
	}

	const	PINFO*	GetPInfo(void)
	{
		return &m_tPlayer;
	}

	vector<CItem*>* GetVector(void)
	{
		return &m_vecInven;
	}

	QSLOT*	GetQuick(void)
	{
		return &m_Quick;
	}

	EINFO*	GetEquip(void)
	{
		return &m_tEquip;
	}

public:
	CPlayer(void);
	virtual ~CPlayer(void);
};
